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
				mAnim->SetDrawOrder(20);
				mAnim->SetAnimFPS(8);

				mBody = new Body(this, "EnemyBee");
				mBody->SetWidthAndHeight(500.f, 400.f);
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				if (pattern == 0)
					SetStageState(new StraightBeeActive(this, p1, p2));
				else
					SetStageState(new CircleBeeActive(this, p1, p2, pattern));

			}

			Bee::~Bee()
			{
			}

			void Bee::BreakBody()
			{
				mBody->SetWidthAndHeight(0.f, 0.f);
			}


			StraightBeeActive::StraightBeeActive(Bee* bee, const GameLib::Vector2& p1, const GameLib::Vector2& p2)
				:StageState()
				, mBee(bee)
				, mPoint1((p2 - p1) / 2.f + p1)
				, mMoveVec((p1 - p2) / 2.f)
				, mCnt(0)
			{

			}
		

			StraightBeeActive::~StraightBeeActive()
			{
			}

			StageState* StraightBeeActive::Update()
			{
				GameLib::Vector2 prePos = mBee->GetPosition();

				float rate = 4.f;
				float l = mMoveVec.Length();
				mBee->SetPosition(mPoint1 + mMoveVec * GameLib::Math::Cos(mCnt / l * rate));

				GameLib::Vector2 dirVec = mBee->GetPosition() - prePos;
				float rot = GameLib::Math::Atan2(dirVec.x, dirVec.y);
				mBee->SetRotation(rot + GameLib::Math::Pi / 2.f);

				mCnt++;

				return this;
			}

			void StraightBeeActive::Hit(Body* myBody, Body* theBody)
			{
				ActiveBeeHit(mBee,myBody, theBody);
			}

			void StraightBeeActive::AdjustPosSub(const GameLib::Vector2& vec)
			{
				mPoint1 += vec;
			}

			CircleBeeActive::CircleBeeActive(Bee* bee,const GameLib::Vector2& p1, const GameLib::Vector2& p2,int pattern)
				:StageState()
				,mBee(bee)
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
				float d = 0.02f;

				GameLib::Vector2 pos = mCenter + GameLib::Vector2::Rotation(mRediusVec, mRot);
				mBee->SetPosition(pos);
				GameLib::Vector2 vec = pos - mCenter;
				float rot= GameLib::Math::Atan2(vec.x, vec.y);
				if (mIsClockwise)
				{
					mRot += d;
					mBee->SetRotation(rot + GameLib::Math::Pi);
				}
				else
				{
					mRot -= d;
					mBee->SetRotation(rot);
				}

				return this;
			}

			void CircleBeeActive::Hit(Body* myBody, Body* theBody)
			{
				ActiveBeeHit(mBee,myBody, theBody);
			}

			void CircleBeeActive::AdjustPosSub(const GameLib::Vector2& vec)
			{
				mCenter += vec;
			}

			void ActiveBeeHit(Bee* myBee, Body* myBody, Body* theBody)
			{
				std::string name = theBody->GetName();

				if (name == "Meteor" || name == "Fork" || name == "Beam")
				{
					myBee->BreakBody();
					myBee->GetAnim()->SetChannel(1);
					myBee->SetStageState(new Fall(myBee));
				}
			}

		}
	}
}

