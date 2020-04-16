#include"Missile.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/Player/Player.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"EnemyState.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{

			MissileBody::MissileBody(StageScene* scene, Missile* mi, int updateOrder)
				:StageActor(scene,mi->GetPosition(),updateOrder)
				,mMissile(mi)
			{
				SetScale(0.1f);

				mBody = new Body(this, "EnemyMissile", 600.f, 300.f);
				mBody->SetAdjust(GameLib::Vector2(0.f, 150.f));
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				mWeakness = new Body(this, "EnemyMissileWeakness", 600.f, 300.f);
				mWeakness->SetAdjust(GameLib::Vector2(0.f, -150.f));
				mWeakness->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));
			}

			MissileBody::~MissileBody()
			{
			}

			void MissileBody::UpdateStageActor()
			{
				SetPosition(mMissile->GetPosition());
			}

			void MissileBody::Hit(Body* myBody, Body* theBody)
			{
				std::string myName = myBody->GetName();
				std::string theName = theBody->GetName();

				if ((theName == "Player" && myName == "EnemyMissileWeakness")||
					theName=="Fork"||theName=="Beam"||theName=="Meteor")
				{
					SetState(GameLib::Actor::State::Dead);
					mMissile->GetAnim()->SetChannel(1);
					mMissile->SetStageState(new Fall(mMissile));
				}


			}

			Missile::Missile(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:StageStateActor(scene,pos,updateOrder)
			{
				SetScale(0.1f);

				mBody = new MissileBody(scene, this);

				GameLib::Animation active = {
					GameLib::Data::GetTexture("../Assets/Enemy/Missile/active.png"),
				};
				GameLib::Animation death = {
					GameLib::Data::GetTexture("../Assets/Enemy/Missile/death.png"),
				};
				std::vector<GameLib::Animation> anim = { active,death };
				mAnim = new GameLib::AnimComponent(this, anim);
				
				SetStageState(new MissileState::Stay(this));

			}

			Missile::~Missile()
			{
			}

			namespace MissileState
			{
				Stay::Stay(Missile* m)
					:StageState()
					, mMissile(m)
				{

				}
				Stay::~Stay()
				{

				}
				StageState* Stay::Update()
				{
					auto pos = mMissile->GetPosition();

					if (pos.x < WINDOW_WIDTH + 100.f)
						return new Active(mMissile);

					return this;
				}

				Active::Active(Missile* m)
					:StageState()
					, mMissile(m)
				{

				}

				Active::~Active()
				{

				}

				StageState* Active::Update()
				{
					auto playerPos = mMissile->GetStageScene()->GetPlayer()->GetPosition();
					auto myPos = mMissile->GetPosition();
					
					float speed = 1.f;

					float d = GameLib::Math::Abs(playerPos.x - myPos.x);

					bool isDown = playerPos.y - myPos.y > 0.f;

					float rot = GameLib::Math::Pi / 4.f * GameLib::Math::Sin(d / 100.f);
					mMissile->SetRotation(rot);

					myPos.x -= speed;
					if (GameLib::Math::Abs(playerPos.x - myPos.x) < 110.f)
					{

						float rot = GameLib::Math::Pi / 2.f * (1.f-(GameLib::Math::Abs(playerPos.x - myPos.x)-10.f) / 100.f);
						if (rot > GameLib::Math::Pi / 2.f)
							rot = GameLib::Math::Pi / 2.f;

						if (!isDown)
							rot *= -1.f;
						mMissile->SetRotation(rot);

						if (isDown)
							myPos.y += 0.5f;
						else
							myPos.y -= 0.5f;

						
						if (GameLib::Math::Abs(playerPos.x - myPos.x) < 10.f)
							return new Go(mMissile, isDown);
						
							
					}

					mMissile->SetPosition(myPos);
					return this;
				}

				Go::Go(Missile* m, bool isDown)
					:StageState()
					, mMissle(m)
					, mIsDown(isDown)
				{
					if (mIsDown)
						mMissle->SetRotation(GameLib::Math::Pi / 2.f);
					else
						mMissle->SetRotation(-GameLib::Math::Pi / 2.f);
				}

				Go::~Go()
				{

				}

				StageState* Go::Update()
				{

					auto pos = mMissle->GetPosition();


					float speed = 6.f;

					if (mIsDown)
						pos.y += speed;
					else
						pos.y -= speed;

					mMissle->SetPosition(pos);

					if (ActorUpdateScope::Left + 100.f > pos.x || ActorUpdateScope::Right - 100.f < pos.x ||
						ActorUpdateScope::Top + 100.f > pos.y || ActorUpdateScope::Bottom - 100.f < pos.y)
						mMissle->SetState(GameLib::Actor::State::Dead);

					return this;
				}


			}

		}
	}
}