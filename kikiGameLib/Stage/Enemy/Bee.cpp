#include"Bee.hpp"
#include"EnemyState.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"Stage/CollisionDetection/Body.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{



			Bee::Bee(StageScene* scene, int pattern, const GameLib::Vector2& p1, const GameLib::Vector2& p2)
				:StageStateActor(scene, p1)
			{
				SetScale(0.08f);

				GameLib::Animation active = {
					GameLib::Data::GetTexture("../Assets/Enemy/bee001.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/bee002.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/bee003.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/bee002.png")
				};
				GameLib::Animation fall = {
					GameLib::Data::GetTexture("../Assets/Enemy/bee-fall.png")
				};
				std::vector<GameLib::Animation> anims = { active,fall };
				mAnim = new GameLib::AnimComponent(this, anims);
				mAnim->SetAnimFPS(8);

				mBody = new Body(this, "EnemyBee");
				mBody->SetWidthAndHeight(500.f, 400.f);
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				if (pattern == 0)
					SetStageState(new StraitBeeActive(this, p1, p2));
				else
					SetStageState(new CircleBeeActive(this, p1, p2, pattern));

			}

			Bee::~Bee()
			{
			}


			StraitBeeActive::StraitBeeActive(Bee* bee, const GameLib::Vector2& p1, const GameLib::Vector2& p2)
				:StageState()
				, mBee(bee)
				, mPoint1(p1)
				, mMoveVec(p2 - p1)
				,mCnt(0)
			{
			}
		

			StraitBeeActive::~StraitBeeActive()
			{
			}

			StageState* StraitBeeActive::Update()
			{
				GameLib::Vector2 prePos = mBee->GetPosition();

				float rate = 1.f;
				float l = mMoveVec.Length();
				mBee->SetPosition(mPoint1 + mMoveVec * GameLib::Math::Sin(mCnt / l * rate));

				GameLib::Vector2 dirVec = mBee->GetPosition() - prePos;
				float rot = GameLib::Math::Atan2(dirVec.x, dirVec.y);
				mBee->SetRotation(rot + GameLib::Math::Pi / 2.f);

				return this;
			}

			void StraitBeeActive::Hit(Body* myBody, Body* theBody)
			{
				ActiveBeeHit(myBody, theBody);
			}

			void StraitBeeActive::AdjustPosSub(const GameLib::Vector2& vec)
			{
				mPoint1 += vec;
			}

			CircleBeeActive::CircleBeeActive(Bee* bee,const GameLib::Vector2& p1, const GameLib::Vector2& p2,int pattern)
				:StageState()
				,mCenter(p1)
				,mRediusVec(p2-p1)
				,mRot(0.f)
				,mIsClockwise(pattern==1)
			{
				mBee->SetPosition(p2);
			}

			CircleBeeActive::~CircleBeeActive()
			{
			}

			StageState* CircleBeeActive::Update()
			{
				float d = 0.01f;

				mBee->SetPosition(mCenter + GameLib::Vector2::Rotation(mRediusVec, mRot));
				mBee->SetRotation(mRot + GameLib::Math::Pi / 2.f);

				if (mIsClockwise)
					mRot += d;
				else
					mRot -= d;

				return this;
			}

			void CircleBeeActive::Hit(Body* myBody, Body* theBody)
			{
				ActiveBeeHit(myBody, theBody);
			}

			void CircleBeeActive::AdjustPosSub(const GameLib::Vector2& vec)
			{
				mCenter += vec;
			}

			void ActiveBeeHit(Body* myBody, Body* theBody)
			{
			}

		}
	}
}

