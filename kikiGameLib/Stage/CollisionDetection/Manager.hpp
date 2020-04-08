#pragma once
#include<vector>

namespace Game
{
	namespace Stage
	{
		class Body;

		class Cell;
		class LinerObject;

		class Liner4Tree
		{
		public:

			Liner4Tree(unsigned int level, float left, float top, float right, float bottom);
			~Liner4Tree();

			bool Regist(LinerObject* obj);
			void SearchCellArray();
			void CheckDelete(unsigned int elem);

		private:
			//SearchCellArray�ōċA�I�Ɏg�p
			void SearchCellArraySub(std::vector<LinerObject*>& colStac, unsigned int Elem);

			bool CreateNewCell(unsigned int Elem);

			//���[�g���ԍ��֌W
			//���W����CellArry�̓Y���������o
			unsigned int GetMortonNumber(float left, float top, float right, float bottom);
			//�r�b�g�����֐�
			unsigned int BitSeparate32(unsigned int n);
			//2D���[�g����Ԕԍ��Z�o�֐�
			unsigned short Get2DMortonNumber(unsigned short x, unsigned short y);
			//���W���烂�[�g���ԍ�
			unsigned int GetPointElem(float pos_x, float pos_y);


			Cell** mCellArray;

			float mWidth;
			float mHeight;
			float mLeft;
			float mTop;
			float mUnitW;
			float mUnitH;
			unsigned int mCellNum;
			unsigned int mLevel;
		};



		class Cell
		{
		public:
			Cell(Liner4Tree* tree, unsigned int elem);
			~Cell();

			bool Push(LinerObject* obj);

			LinerObject* GetFirstObject() const { return mFirstObject; }
			void SetFirstObject(LinerObject* obj) { mFirstObject = obj; }

			unsigned int GetElm() const { return mElem; }
			Liner4Tree* GetTree() const { return mTree; }

		private:
			Liner4Tree* mTree;
			LinerObject* mFirstObject;
			unsigned int mElem;
		};

		class LinerObject
		{
		public:
			LinerObject(Body* body);
			~LinerObject();

			void RemoveFromList();

			LinerObject* mPre;
			LinerObject* mNext;

			//�������
			Cell* mCell;

			Body* GetBody() const { return mBody; }

		private:
			Body* mBody;

		};
	}
}