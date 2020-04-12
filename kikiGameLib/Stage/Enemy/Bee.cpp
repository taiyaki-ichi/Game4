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

				if (pattern == 0)
					SetStageState(new StraightBeeActive(this, p1, p2));
				else
					SetStageState(new CircleBeeActive(this, p1, p2, pattern));

				new BeeBody(scene, this);
			}

			Bee::~Bee()
			{
			}

			BeeBody::BeeBody(StageScene* scene, Bee* bee, int updateOrder)
				:StageActor(scene, updateOrder)
				, mBee(bee)
			{
				SetPosition(mBee->GetPosition());

				SetScale(0.08f);

				mBody = new Body(this, "EnemyBee", 500.f, 200.f);
				mBody->SetAdjust(GameLib::Vector2(0.f, 100.f));
				mBody->SetColor(GameLib::Vector3(0, 0, 255));

				mWeakness = new Body(this, "EnemyBeeWeakness", 500.f, 200.f);
				mWeakness->SetAdjust(GameLib::Vector2(0.f, -100.f));
				mWeakness->SetColor(GameLib::Vector3(255, 0, 0));

			}

			BeeBody::~BeeBody()
			{
			}

			void BeeBody::UpdateStageActor()
			{
				SetPosition(mBee->GetPosition());
			}

			void BeeBody::Hit(Body* myBody, Body* theBody)
			{
				std::string name = theBody->GetName();
				std::string myName = myBody->GetName();

				if (name == "Meteor" || name == "Fork" || name == "Beam")
				{
					mBody->SetWidthAndHeight(0.f, 0.f);
					mWeakness->SetWidthAndHeight(0.f, 0.f);
					mBee->GetAnim()->SetChannel(1);
					mBee->SetStageState(new Fall(mBee));
					SetState(GameLib::Actor::State::Dead);
				}
				else if (name == "Player" && myName == "EnemyBeeWeakness")
				{
					mBody->SetWidthAndHeight(0.f, 0.f);
					mWeakness->SetWidthAndHeight(0.f, 0.f);
					mBee->GetAnim()->SetChannel(1);
					mBee->SetStageState(new Fall(mBee));
					SetState(GameLib::Actor::State::Dead);
				}
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

			void CircleBeeActive::AdjustPosSub(const GameLib::Vector2& vec)
			{
				mCenter += vec;
			}




}
	}
}

