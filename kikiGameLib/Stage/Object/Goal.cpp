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
			Rect::Rect(StageScene* scene,Goal* goal, const GameLib::Vector2& pos)
				:StageActor(scene,pos)
				,mGoal(goal)
			{
				new RectangleComponent(this, 2.f, 2.f, GameLib::Color::Black,200);
			}
			Rect::~Rect()
			{
			}
			void Rect::UpdateStageActor()
			{
				SetRotation(GetRotation() + 0.2f);

				auto targetPos = mGoal->GetPosition() + GameLib::Vector2(100.f, 100.f);
				auto pos = GetPosition();
				auto vec = targetPos - pos;
				if (vec.Length() < 5.f)
					SetState(GameLib::Actor::State::Dead);

				float speed = 4.f;
				SetPosition(pos + GameLib::Vector2::Normalize(vec) * speed);

			}

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
			SetScale(0.5f);

			auto texture1 = new GameLib::TextureComponent(this, "../Assets/Other/goal.png", -10);
			texture1->SetAdjust(GameLib::Vector2(-150.f, 0.f));

			

			auto texture2 = new GameLib::TextureComponent(this, "../Assets/Other/goal.png", 1200);
			texture2->SetAdjust(GameLib::Vector2(150.f, 0.f));

			auto body = new Body(this, "Goal", 400.f, 500.f);
			body->SetAdjust(GameLib::Vector2(0.f, 130.f));
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

			int r1 = std::rand() % 100;
			int r2 = std::rand() % 100;

			float y = pos.y - 300.f + static_cast<float>(600 * r1)/100.f;
			float x = pos.x - 400.f * r2 / 100.f;

			new GoalParts::Rect(GetStageScene(), this, GameLib::Vector2(x, y));

			int r = std::rand() % 100;
			if (r % 10 == 0)
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