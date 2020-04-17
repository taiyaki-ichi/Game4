#include"Goal.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Draw/RectangleComponent.hpp"

namespace Game
{
	namespace Stage
	{
		namespace GoalParts
		{
			

			const int Kira::DEATHTIME = 60;
			const float Kira::MAXSCALE = 0.15f;

			Kira::Kira(StageScene* scene, const GameLib::Vector2& pos)
				:StageActor(scene,pos)
				,mCnt(0)
			{
				SetScale(0.f);
				new GameLib::TextureComponent(this, "../Assets/Other/kira.png", 1300);
			}
			Kira::~Kira()
			{
			}
			void Kira::UpdateStageActor()
			{
				if (mCnt < DEATHTIME / 2.f)
				{
					float t = DEATHTIME / 2.f;
					SetScale(GetScale() + MAXSCALE / t);
				}
				else
				{
					float t = DEATHTIME / 2.f;
					float scale = GetScale() - MAXSCALE / t;
					if (scale < 0.f)
					{
						scale = 0.f;
						SetState(GameLib::Actor::State::Dead);
					}
					SetScale(scale);
				}
				mCnt++;
			}
		}


		Goal::Goal(StageScene* scene, const GameLib::Vector2& pos)
			:StageActor(scene,pos)
		{

			SetScale(0.8f);
			auto texture = new GameLib::TextureComponent(this, "../Assets/Other/goal.png", -10);
			auto body = new Body(this, "Goal", 300.f, 300.f);
			body->SetAdjust(GameLib::Vector2(0.f, 230.f));
			body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));


		}

		Goal::~Goal()
		{
		}

		void Goal::UpdateStageActor()
		{
			auto pos = GetPosition();
			pos.y += 1.f;
			SetPosition(pos);

			int r = std::rand() % 100;
			if (r % 30 == 0)
			{
				float range = 600;

				int r3 = std::rand() % 100;
				int r4 = std::rand() % 100;

				auto kiraPos = pos - GameLib::Vector2(range / 2.f, range / 2.f);
				kiraPos += GameLib::Vector2(range * r3 / 100.f, range * r4 / 100.f);

				new GoalParts::Kira(GetStageScene(), kiraPos);

			}

		}

		void Goal::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Ground")
			{
				auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, 0.f, 0.f);
				SetPosition(GetPosition() + adjust);
			}
		}

	}
}