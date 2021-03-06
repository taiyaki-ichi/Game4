#include"Carrot.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Data.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/Player/Player.hpp"
#include"EnemyState.hpp"
#include"Stage/Object/Trampoline.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{

			const float Carrot::ACTIVERNGE = 400.f;

			Carrot::Carrot(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:StageStateActor(scene,pos,updateOrder)
			{
				SetScale(0.12f);

				GameLib::Animation stay = {
					GameLib::Data::GetTexture("../Assets/Enemy/Carrot/stay.png"),
				};
				GameLib::Animation run = {
					GameLib::Data::GetTexture("../Assets/Enemy/Carrot/run001.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Carrot/run002.png"),
				};
				GameLib::Animation flat = {
					GameLib::Data::GetTexture("../Assets/Enemy/Carrot/flat.png"),
				};
				std::vector<GameLib::Animation> anim = { stay,run ,flat };
				mAnim = new GameLib::AnimComponent(this, anim);
				mAnim->SetDrawOrder(20);
				mAnim->SetAnimFPS(10);

				mBody = new Body(this, "EnemyCarrot",450.f,200.f);
				mBody->SetAdjust(GameLib::Vector2(-50.f, 100.f));
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				mWeakness = new Body(this, "EnemyCarrotWeakness", 410.f, 100.f);
				mWeakness->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));
				mWeakness->SetAdjust(GameLib::Vector2(-30.f, -45.f));


				SetStageState(new CarrotState::Stay(this));

			}

			Carrot::~Carrot()
			{
			}

			void Carrot::BreakBody()
			{
				mBody->SetWidthAndHeight(0.f, 0.f);
				mWeakness->SetWidthAndHeight(0.f, 0.f);
			}

			void Carrot::GoRight()
			{
				mBody->SetAdjust(GameLib::Vector2(50.f, 100.f));
				mWeakness->SetAdjust(GameLib::Vector2(30.f, -45.f));
				mAnim->SetTextureFlip(GameLib::TextureFlip::Horizontal);
			}

			void Carrot::GoLeft()
			{
				mBody->SetAdjust(GameLib::Vector2(-50.f, 100.f));
				mWeakness->SetAdjust(GameLib::Vector2(-30.f, -45.f));
				mAnim->SetTextureFlip(GameLib::TextureFlip::None);
			}


			namespace CarrotState
			{

				const float Active::MAXSPEED = 6.f;
				const float Active::RUNPOER = 0.2f;

				Active::Active(Carrot* carrot,float vY)
					:StageState()
					,mCarrot(carrot)
					,mVelocity(0.f,vY)
				{
					mCarrot->GetAnim()->SetChannel(1);
				}

				Active::~Active()
				{
				}

				StageState* Active::Update()
				{
					auto playerPos = mCarrot->GetStageScene()->GetPlayer()->GetPosition();
					auto myPos = mCarrot->GetPosition();

					if ((playerPos - myPos).Length() > Carrot::ACTIVERNGE + 20.f)
						return new Stay(mCarrot);

					if (playerPos.x - myPos.x > 0.f)
						mVelocity.x += RUNPOER;
					else
						mVelocity.x -= RUNPOER;

					if (mVelocity.x > MAXSPEED)
						mVelocity.x = MAXSPEED;
					else if (mVelocity.x < -MAXSPEED)
						mVelocity.x = -MAXSPEED;

					if (mVelocity.x > 0.f)
						mCarrot->GoRight();
					else
						mCarrot->GoLeft();

					mVelocity.y += GRAVITYPOWER;
					myPos += mVelocity;
					mCarrot->SetPosition(myPos);

					return this;
				}

				void Active::Hit(Body* myBody, Body* theBody)
				{
					std::string theName = theBody->GetName();
					std::string myName = myBody->GetName();

					if (theName == "Ground"||theName=="Container")
					{
						auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, MAXSPEED);
						if (adjust.y < 0.f)
						{
							adjust += theBody->GetVelocity();
							mVelocity.y = 0.f;
						}
						mCarrot->SetPosition(mCarrot->GetPosition() + adjust);
					}
					else if (theName == "Player" && myName == "EnemyCarrotWeakness")
					{
						mCarrot->GetAnim()->SetChannel(2);
						mCarrot->BreakBody();

						mCarrot->SetStageState(new DeathTimerState(mCarrot, 30));
					}
					else if (theName == "Beam" || theName == "Meteor")
					{
						mCarrot->BreakBody();
						mCarrot->GetAnim()->SetChannel(0);
						mCarrot->SetStageState(new Fall(mCarrot));
					}
					else if (theName == "Trampoline")
					{
						auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, MAXSPEED);
						if (adjust.y < 0.f)
						{
							adjust += theBody->GetVelocity();
							mVelocity.y = -Trampoline::ENEMYPOWER;
						}
						mCarrot->SetPosition(mCarrot->GetPosition() + adjust);
					}
				}

				Stay::Stay(Carrot* carrot)
					:StageState()
					,mCarrot(carrot)
					,mVelocityY(0.f)
				{
					mCarrot->GetAnim()->SetChannel(0);
				}

				Stay::~Stay()
				{
				}

				StageState* Stay::Update()
				{
					auto playerPos = mCarrot->GetStageScene()->GetPlayer()->GetPosition();
					auto myPos = mCarrot->GetPosition();

					if ((playerPos - myPos).Length() < Carrot::ACTIVERNGE - 20.f)
						return new Active(mCarrot, mVelocityY);

					mVelocityY += GRAVITYPOWER;
					myPos.y += mVelocityY;
					mCarrot->SetPosition(myPos);

					return this;
				}

				void Stay::Hit(Body* myBody, Body* theBody)
				{
					std::string name = theBody->GetName();


					if (name == "Ground"||name=="Container")
					{
						auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, 0.f);
						if (adjust.y < 0.f)
						{
							adjust += theBody->GetVelocity();
							mVelocityY = 0.f;
						}
						mCarrot->SetPosition(mCarrot->GetPosition() + adjust);
					}
					else if (name == "Beam" || name == "Meteor")
					{
						mCarrot->BreakBody();
						mCarrot->GetAnim()->SetChannel(0);
						mCarrot->SetStageState(new Fall(mCarrot));
					}
					else if (name == "Trampoline" )
					{
						auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, 0.f);
						if (adjust.y < 0.f)
						{
							adjust += theBody->GetVelocity();
							mVelocityY = -Trampoline::ENEMYPOWER;
						}
						mCarrot->SetPosition(mCarrot->GetPosition() + adjust);
					}
				}

			}
		}
	}
}