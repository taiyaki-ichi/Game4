#include"Toge.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"EnemyState.hpp"


namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{

			Toge::Toge(StageScene* scene, const GameLib::Vector2& pos)
				:StageStateActor(scene,pos)
			{
				SetScale(0.1f);

				GameLib::Animation active = {
					GameLib::Data::GetTexture("../Assets/Enemy/toge.png"),
				};
				GameLib::Animation fall = {
					GameLib::Data::GetTexture("../Assets/Enemy/toge.png"),
				};
				std::vector<GameLib::Animation> anim = { active,fall };
				mAnim = new GameLib::AnimComponent(this, anim);
				mAnim->SetDrawOrder(20);

				mBody = new Body(this, "EnemyToge");
				mBody->SetWidthAndHeight(550.f, 550.f);
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				SetStageState(new TogeActive(this));
			}

			Toge::~Toge()
			{
			}


			void Toge::BreakBody()
			{
				mBody->SetWidthAndHeight(0.f, 0.f);
			}

			TogeActive::TogeActive(Toge* toge)
				:StageState()
				,mToge(toge)
				,mTimer(0.f)
			{
			}

			TogeActive::~TogeActive()
			{
			}

			StageState* TogeActive::Update()
			{
				using Vec2 = GameLib::Vector2;
				Vec2 pos = mToge->GetPosition();

				//d—Í
				pos.y += GRAVITY;
				mToge->SetPosition(pos);

				mTimer += 0.01f;

				mToge->SetScale(0.15f + 0.05f * GameLib::Math::Sin(GameLib::Math::Pi / 3.f * mTimer));

				return this;
			}

			void TogeActive::Hit(Body* myBody, Body* theBody)
			{
				std::string name = theBody->GetName();

				if (name == "Ground" || name == "Container")
				{
					using Vec2 = GameLib::Vector2;
					Vec2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, 0.f);

					if (adjust.y < 0.f)
						adjust += theBody->GetVelocity();
					mToge->SetPosition(mToge->GetPosition() + adjust);
				}
				else if (name == "Meteor" || name == "Beam")
				{
					mToge->GetAnim()->SetChannel(1);
					mToge->BreakBody();
					mToge->SetStageState(new Fall(mToge));
				}
			}

		}
	}

}