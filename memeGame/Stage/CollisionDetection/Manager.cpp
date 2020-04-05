#include"Manager.hpp"
#include"include/Math.hpp"
#include"Body.hpp"
#include"include/Actor.hpp"
#include"CollisionDetection.hpp"
#include"Stage/StageActor.hpp"


namespace Game
{

	namespace Stage
	{
		Liner4Tree::Liner4Tree(unsigned int level, float left, float top, float right, float bottom)
			:mCellArray(nullptr)
			, mLeft(left)
			, mTop(top)
			, mWidth(right - left)
			, mHeight(bottom - top)
			, mUnitW((right - left) / (1 << level))
			, mUnitH((bottom - top) / (1 << level))
			, mLevel(level)
		{

			mCellNum = (static_cast<int>(GameLib::Math::Pow(4.f, level + 1)) - 1) / 3;

			mCellArray = new Cell * [mCellNum];
			for (int i = 0; i < mCellNum; i++) {
				mCellArray[i] = nullptr;
			}
		}
		Liner4Tree::~Liner4Tree()
		{
			if (mCellArray != nullptr) {
				for (unsigned int i = 0; i < mCellNum; i++) {
					if (mCellArray[i] != nullptr) {
						delete mCellArray[i];
					}
				}
				delete[] mCellArray;
			}
		}

		bool Liner4Tree::Regist(LinerObject* obj)
		{
			auto body = obj->GetBody();

			using Vec2 = GameLib::Vector2;
			float rot = body->GetOwner()->GetRotation();
			auto pos = body->GetOwner()->GetPosition() + Vec2::Rotation(body->GetAdjust(), rot);
			float w = body->GetRotatedWidth();
			float h = body->GetRotatedHeight();

			float left = pos.x - w / 2.f;
			float right = pos.x + w / 2.f;
			float top = pos.y - h / 2.f;
			float bottom = pos.y + h / 2.f;

			unsigned int Elem = GetMortonNumber(left, top, right, bottom);

			if (Elem < mCellNum)
			{
				//��ԃI�u�W�F�N�g���Ȃ��ꍇ�͐V�K�쐬
				if (!mCellArray[Elem]) {
					CreateNewCell(Elem);
				}

				return mCellArray[Elem]->Push(obj);
			}
			return false;
		}

		void Liner4Tree::SearchCellArray()
		{
			if (mCellArray[0] != nullptr) {

				//���`�T��
				std::vector<LinerObject*> ColStac;
				SearchCellArraySub(ColStac, 0);
			}
		}

		void Liner4Tree::CheckDelete(unsigned int elem)
		{
			unsigned int e = (elem << 2) + 1;
			if (mCellArray[e] == nullptr &&
				mCellArray[e + 1] == nullptr &&
				mCellArray[e + 2] == nullptr &&
				mCellArray[e + 3] == nullptr)
			{
				delete mCellArray[elem];
				mCellArray[elem] = nullptr;
				CheckDelete((elem - 1) >> 2);
			}

		}

		void Liner4Tree::SearchCellArraySub(std::vector<LinerObject*>& colStac, unsigned int Elem)
		{
			//������ԃI�u�W�F�N�g�ɏ���������̓��m�̔���
			auto rect1 = mCellArray[Elem]->GetFirstObject();
			Body* body1;
			Body* body2;
			while (rect1 != nullptr)
			{
				auto rect2 = rect1->mNext;
				while (rect2 != nullptr)
				{
					body1 = rect1->GetBody();
					body2 = rect2->GetBody();
					if (CollisionDetection(body1, body2))
					{
						rect1->GetBody()->GetStageOwner()->Hit(body1, body2);
						rect2->GetBody()->GetStageOwner()->Hit(body2, body1);
					}

					rect2 = rect2->mNext;
				}

				//�X�^�b�N�ɕۑ�����Ă���obj1���傫����Ԃɏ������Ă���
				//StageObject�Ƃ̂����蔻��
				if (colStac.size() != 0)
				{
					for (auto rect : colStac)
					{
						if (rect != nullptr)
						{
							body1 = rect->GetBody();
							body2 = rect1->GetBody();
							if (CollisionDetection(body1, body2))
							{
								body1->GetStageOwner()->Hit(body1, body2);
								body2->GetStageOwner()->Hit(body2, body1);

							}
						}
					}
				}

				rect1 = rect1->mNext;
			}

			//�q��Ԃ̏���

			bool ChildFlag = false;
			//�q��Ԃ̃I�u�W�F�N�g�̐�
			unsigned int ObjNum = 0;
			unsigned int i;
			unsigned int NextElem;

			for (i = 0; i < 4; i++)
			{
				NextElem = Elem * 4 + 1 + i;
				if (NextElem < mCellNum && mCellArray[NextElem] != nullptr)
				{
					if (ChildFlag == false)
					{

						rect1 = mCellArray[Elem]->GetFirstObject();
						while (rect1 != nullptr)
						{
							colStac.emplace_back(rect1);
							ObjNum++;
							rect1 = rect1->mNext;
						}

					}

					//�X�^�b�N�ɒǉ�����I�u�W�F�N�g�̏d����h��
					ChildFlag = true;

					//�q��Ԃ�
					SearchCellArraySub(colStac, Elem * 4 + 1 + i);
				}

			}

			//�߂��Ă�����X�^�b�N�ɒǉ����������폜����
			if (ChildFlag == true)
			{
				for (i = 0; i < ObjNum; i++) {
					colStac.pop_back();
				}
			}

		}

		bool Liner4Tree::CreateNewCell(unsigned int Elem)
		{
			while (mCellArray[Elem] == nullptr)
			{
				mCellArray[Elem] = new Cell(this, Elem);

				//�e��ԂփW�����v
				Elem = (Elem - 1) >> 2;
				if (Elem >= mCellNum)
					break;
			}
			return true;
		}

		unsigned int Liner4Tree::GetMortonNumber(float left, float top, float right, float bottom)
		{
			//�ŏ����x���ɂ����郂�[�g���ԍ�
			unsigned int LT = GetPointElem(left, top);
			unsigned int RB = GetPointElem(right, bottom);

			//�r���I�_���a���珊�����x�������o
			unsigned int Def = RB ^ LT;
			unsigned int HiLevel = 0;
			unsigned int i;
			for (i = 0; i < mLevel; i++)
			{
				unsigned int Check = (Def >> (i * 2)) & 0x3;
				if (Check != 0) {
					HiLevel = i + 1;
				}
			}
			unsigned int SpaceNum = RB >> (HiLevel * 2);
			unsigned int AddNum = (static_cast<int>(GameLib::Math::Pow(4.f, mLevel - HiLevel)) - 1) / 3;
			SpaceNum += AddNum;

			if (SpaceNum > mCellNum)
				return 0xffffffff;

			return SpaceNum;
		}

		unsigned int Liner4Tree::BitSeparate32(unsigned int n)
		{
			n = (n | (n << 8)) & 0x00ff00ff;
			n = (n | (n << 4)) & 0x0f0f0f0f;
			n = (n | (n << 2)) & 0x33333333;
			return (n | (n << 1)) & 0x55555555;
		}

		unsigned short Liner4Tree::Get2DMortonNumber(unsigned short x, unsigned short y)
		{
			return (unsigned short)(BitSeparate32(x) | (BitSeparate32(y) << 1));
		}

		unsigned int Liner4Tree::GetPointElem(float pos_x, float pos_y)
		{
			return Get2DMortonNumber((unsigned short)((pos_x - mLeft) / mUnitW), (unsigned short)((pos_y - mTop) / mUnitH));
		}

		Cell::Cell(Liner4Tree* tree, unsigned int elem)
			:mTree(tree)
			, mFirstObject(nullptr)
			, mElem(elem)
		{
		}
		Cell::~Cell()
		{
		}
		bool Cell::Push(LinerObject* obj)
		{
			if (obj == nullptr)
				return false;

			//��d�o�^�̖h�~
			if (obj->mCell == this)
				return false;

			if (mFirstObject == nullptr)
			{
				mFirstObject = obj;
			}
			else
			{
				obj->mNext = mFirstObject;
				mFirstObject->mPre = obj;
				mFirstObject = obj;
			}

			//��Ԃ�o�^
			obj->mCell = this;

			return true;
		}

		LinerObject::LinerObject(Body* body)
			:mBody(body)
			, mPre(nullptr)
			, mNext(nullptr)
			, mCell(nullptr)
		{
		}

		LinerObject::~LinerObject()
		{
		}

		void LinerObject::RemoveFromList()
		{
			if (mCell != nullptr) {
				if (mCell->GetFirstObject() == this)
				{
					mCell->SetFirstObject(mNext);
					//if (mNext == nullptr)
						//mCell->GetTree()->CheckDelete(mCell->GetElm());

				}

				if (mPre != nullptr)
				{
					mPre->mNext = mNext;
				}
				if (mNext != nullptr)
				{
					mNext->mPre = mPre;
				}

				mPre = nullptr;
				mNext = nullptr;
				mCell = nullptr;

			}
		}
	}
}