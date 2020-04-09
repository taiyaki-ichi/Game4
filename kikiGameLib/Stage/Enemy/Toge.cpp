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
				:StageActor(scene,pos)
			{
				SetScale(0.1f);

				GameLib::Animation anim = {
					GameLib::Data::GetTexture("../Assets/Enemy/toge.png"),
				};
				mAnim = new GameLib::AnimComponent(this, anim);

				mBody = new Body(this, "EnemyToge");
				mBody->SetWidthAndHeight(550.f, 550.f);
				mBody->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));

				mState = new TogeActive(this);
			}

			Toge::~Toge()
			{
			}

			void Toge::UpdateStageActor()
			{
				if (mState)
				{
					StageState* next = mState->Update();
					if (next != mState)
					{
						delete mState;
						mState = next;
					}
				}
			}

			void Toge::Hit(Body* myBody, Body* theBody)
			{
				if (mState)
					mState->Hit(myBody, theBody);
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

				if (name == "Ground")
				{
					using Vec2 = GameLib::Vector2;
					Vec2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, 0.f);

					mToge->SetPosition(mToge->GetPosition() + adjust);
				}
			}

		}
	}

}