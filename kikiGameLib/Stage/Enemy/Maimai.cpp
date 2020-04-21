#include"Maimai.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Enemy/EnemyState.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/Player/Player.hpp"
#include"Stage/Object/Trampoline.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{



			Maimai::Maimai(StageScene* scene, const GameLib::Vector2& pos, int udpdateOrder)
				:StageStateActor(scene,pos,udpdateOrder)
			{
				SetScale(0.1f);

				GameLib::Animation stay = {
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/stay001.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/stay002.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/stay003.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/stay004.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/stay005.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/stay006.png"),
				};
				GameLib::Animation launch = {
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/launch.png"),
				};
				GameLib::Animation death = {
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/death.png"),
				};
				GameLib::Animation flat = {
					GameLib::Data::GetTexture("../Assets/Enemy/Maimai/flat.png"),
				};
				std::vector<GameLib::Animation> anim = { stay,launch,death,flat };

				mAnim = new GameLib::AnimComponent(this, anim);
				mAnim->SetAnimFPS(10);

				mBody = new Body(this, "EnemyMaimai", 600.f, 300.f);
				mBody->SetAdjust(GameLib::Vector2(0.f, 300.f / 2.f + 50.f));
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				mWeakness = new Body(this, "EnemyMaimaiWeakness", 600.f, 300.f);
				mWeakness->SetAdjust(GameLib::Vector2(0.f, -300.f / 2.f + 50.f));
				mWeakness->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));

				SetStageState(new MaimaiState::Active(this));
			}

			Maimai::~Maimai()
			{
			}

			void Maimai::BreakBody()
			{
				mBody->SetWidthAndHeight(0.f, 0.f);
				mWeakness->SetWidthAndHeight(0.f, 0.f);
			}


			namespace MaimaiState
			{
				Active::Active(Maimai* m)
					:StageState()
					, mMaimai(m)
					,mCnt(0)
					,mVelocityY(0.f)
				{

				}

				Active::~Active()
				{

				}

				StageState* Active::Update()
				{
					auto pos = mMaimai->GetPosition();
					mVelocityY += GRAVITYPOWER;
					pos.y += mVelocityY;
					mMaimai->SetPosition(pos);

					auto playerPos = mMaimai->GetStageScene()->GetPlayer()->GetPosition();
					if (playerPos.x - pos.x > 0.f)
						mMaimai->GetAnim()->SetTextureFlip(GameLib::TextureFlip::Horizontal);
					else
						mMaimai->GetAnim()->SetTextureFlip(GameLib::TextureFlip::None);

					if (mCnt == 140)
						mMaimai->GetAnim()->SetChannel(1);
					if (mCnt >= 180)
					{
						if (playerPos.x - pos.x > 0.f)
							new Nail(mMaimai->GetStageScene(), pos + GameLib::Vector2(50.f, 0.f), true);
						else
							new Nail(mMaimai->GetStageScene(), pos - GameLib::Vector2(50.f, 0.f), false);

						mMaimai->GetAnim()->SetChannel(0);
						mCnt = 0;
					}

					mCnt++;
					return this;
				}

				void Active::Hit(Body* myBody, Body* theBody)
				{
					std::string name = theBody->GetName();
					std::string myName = myBody->GetName();

					if (name == "Ground"||name=="Container")
					{
						auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, 0.f);
						if (adjust.y < 0.f)
						{
							mVelocityY = 0.f;
							adjust += theBody->GetVelocity();
						}
						mMaimai->SetPosition(mMaimai->GetPosition() + adjust);
					}
					else if (name == "Player" && myName == "EnemyMaimaiWeakness")
					{
						mMaimai->GetAnim()->SetChannel(3);
						mMaimai->BreakBody();
						mMaimai->SetPosition(mMaimai->GetPosition() + GameLib::Vector2(0.f, -5.f));
						mMaimai->SetStageState(new DeathTimerState(mMaimai, 30));
					}
					else if (name == "Fork" || name == "Beam" || name == "Meteor")
					{
						mMaimai->GetAnim()->SetChannel(2);
						mMaimai->BreakBody();
						mMaimai->SetStageState(new Fall(mMaimai));
					}
					else if (name == "Trampoline" )
					{
						auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, 0.f);
						if (adjust.y < 0.f)
						{
							mVelocityY = -Trampoline::ENEMYPOWER;
							adjust += theBody->GetVelocity();
						}
						mMaimai->SetPosition(mMaimai->GetPosition() + adjust);
					}

				}
			}

			Nail::Nail(StageScene* scene, const GameLib::Vector2& pos, bool isRight, int updateOrder)
				:StageStateActor(scene, pos, updateOrder)
				,mBody(nullptr)
				,mWeakness(nullptr)
			{
				SetScale(0.05f);

				mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/Maimai/nail.png");
				if (isRight)
					mTexture->SetTextureFlip(GameLib::TextureFlip::Horizontal);

				mBody = new Body(this, "Nail", 600.f, 100.f);
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				mWeakness = new Body(this, "NailWeakness", 580.f, 100.f);
				mWeakness->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));

				if (isRight)
				{
					mBody->SetAdjust(GameLib::Vector2(-50.f, 50.f));
					mWeakness->SetAdjust(GameLib::Vector2(-130.f, -50.f));
				}
				else
				{
					mBody->SetAdjust(GameLib::Vector2(50.f, 50.f));
					mWeakness->SetAdjust(GameLib::Vector2(130.f, -50.f));
				}

				SetStageState(new NailState::Active(this, isRight));

			}

			Nail::~Nail()
			{
			}

			void Nail::BreakBody()
			{
				mBody->SetWidthAndHeight(0.f, 0.f);
				mWeakness->SetWidthAndHeight(0.f, 0.f);
			}

		
			namespace NailState
			{

				Active::Active(Nail* n, bool isRight)
					:mNail(n)
					, mIsRight(isRight)
				{

				}

				Active::~Active()
				{

				}

				StageState* Active::Update()
				{
					auto pos = mNail->GetPosition();

					float speed = 6.f;

					if (mIsRight)
						pos.x += speed;
					else
						pos.x -= speed;

					if (ActorUpdateScope::Left + 100.f > pos.x || ActorUpdateScope::Right - 100.f < pos.x ||
						ActorUpdateScope::Top + 100.f > pos.y || ActorUpdateScope::Bottom - 100.f < pos.y)
						mNail->SetState(GameLib::Actor::State::Dead);

					mNail->SetPosition(pos);

					return this;
				}

				void Active::Hit(Body* myBody, Body* theBody)
				{
					std::string name = theBody->GetName();
					std::string myName = myBody->GetName();

					if (name == "Player" && myName == "NailWeakness")
					{
						mNail->BreakBody();
						mNail->SetStageState(new Fall(mNail));
					}
					else if (name == "Meteor" || name == "Beam")
					{
						mNail->BreakBody();
						mNail->SetStageState(new Fall(mNail));
					}
					
				}
			}

		}

	}
}