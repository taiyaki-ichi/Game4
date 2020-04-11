#include"Frog.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Data.hpp"
#include"EnemyState.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{



			Frog::Frog(StageScene* scene, const GameLib::Vector2& pos, float h)
				:StageStateActor(scene,pos)
			{
				SetScale(0.08f);

				GameLib::Animation stay = {
					GameLib::Data::GetTexture("../Assets/Enemy/frog001.png")
				};
				GameLib::Animation jump = {
					GameLib::Data::GetTexture("../Assets/Enemy/frog002.png")
				};
				GameLib::Animation fall = {
					GameLib::Data::GetTexture("../Assets/Enemy/frog003.png")
				};
				GameLib::Animation flat = {
					GameLib::Data::GetTexture("../Assets/Enemy/frog004.png")
				};
				std::vector<GameLib::Animation> anims = {
					stay,
					jump,
					fall,
					flat
				};
				mAnim = new GameLib::AnimComponent(this, anims);

				mBody = new Body(this, "EnemyFrog");
				mBody->SetWidthAndHeight(500.f, 350.f);
				mBody->SetAdjust(GameLib::Vector2(0.f, 150.f));
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 225.f));

				mWeakness = new Body(this, "EnemyFrogWeakness");
				mWeakness->SetWidthAndHeight(500.f, 300.f);
				mWeakness->SetAdjust(GameLib::Vector2(0.f, -175.f));
				mWeakness->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));

				
				int n = 60;
				float d = -0.1f;
				float a = h / n - (n - 1) / 2.f * d;

				SetStageState(new FrogActive(this, -a));

				
			}

			Frog::~Frog()
			{
			}


			void Frog::BreakBody()
			{
				mBody->SetWidthAndHeight(0.f, 0.f);
				mWeakness->SetWidthAndHeight(0.f, 0.f);
			}

			FrogActive::FrogActive(Frog* frog, float jumpPower)
				:StageState()
				, mFrog(frog)
				, mVelocityY(0.f)
				,mOnGround(false)
				,mCnt(0)
				,mJumpPower(jumpPower)
				,mFlatFlag(false)
			{
			}

			FrogActive::~FrogActive()
			{
			}

			StageState* FrogActive::Update()
			{

				if (mCnt >= 60 && mOnGround == true)
				{
					mVelocityY = mJumpPower;
					mFrog->GetAnim()->SetChannel(1);
					mCnt = 0;
					mOnGround = false;
				}


				GameLib::Vector2 pos = mFrog->GetPosition();
				if (mVelocityY < 0.f)
					pos.y += mVelocityY;
				else
					pos.y += 2.f;

				mFrog->SetPosition(pos);

				mVelocityY += 0.1f;
				if (mVelocityY > 0.f)
					mVelocityY = 0.f;
				
				if (mOnGround == true)
					mCnt++;

				if (mFlatFlag)
				{

					mFrog->GetAnim()->SetChannel(3);

					GameLib::Vector2 pos = mFrog->GetPosition();
					pos.y += 10.f;
					mFrog->SetPosition(pos);

					mFrog->BreakBody();

					return new DeathTimerState(mFrog, 30);
				}

				return this;
			}

			void FrogActive::Hit(Body* myBody, Body* theBody)
			{

				std::string name = theBody->GetName();
				std::string myName = myBody->GetName();
				if (name == "Ground")
				{
					GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, 5.f, 0.f);
					if (adjust.y < 0.f)
					{
						mOnGround = true;
						mVelocityY = 0.f;
						mFrog->GetAnim()->SetChannel(0);
					}
					else if(adjust.y)
					{
						mVelocityY = 0.f;
					}

					mFrog->SetPosition(mFrog->GetPosition() + adjust);
				}
				else if (name == "Player" && myName == "EnemyFrogWeakness")
				{
					mFlatFlag = true;
					mFrog->BreakBody();
				}
				else if (name == "Fork")
				{
					mFrog->BreakBody();
					mFrog->SetStageState(new Fall(mFrog));
				}
			}

		}
	}
}