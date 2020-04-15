#include"Meteor.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"WindowData.hpp"
#include"Stage/StageScene.hpp"

namespace Game
{
	namespace Stage
	{
		namespace PlayerAction
		{
			Meteor::Meteor(StageScene* scene, float x, int upateOrder)
				:StageActor(scene,upateOrder)
				,mCnt(0)
			{
				auto pos = GameLib::Vector2(x, -250.f);
				SetPosition(pos);
				float scale = 0.7f;
				SetScale(scale);

				mBody = new Body(this, "Meteor");
				mBody->SetWidthAndHeight(500.f, 300.f);
				mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

				auto body = new Body(this, "Meteor");
				body->SetWidthAndHeight(350.f, 80.f);
				body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
				body->SetAdjust(GameLib::Vector2(0.f, 200.f));

				new GameLib::TextureComponent(this, "../Assets/Action/meteor.png",5);

				mRect = new RectangleComponent(this, 0.f, 1100.f/scale, GameLib::Color::Black, 0,4);
				auto ad = GameLib::Vector2(0.f, 550.f/scale);
				mRect->SetAdjust(ad);
			}

			Meteor::~Meteor()
			{
			}

			void Meteor::UpdateStageActor()
			{
				float w = mRect->GetWidth();
				w += 3.f;
				float bodyWidth = mBody->GetWidth();
				float s = GetScale();
				if (w * s > bodyWidth)
					w = bodyWidth / s;
				mRect->SetWidth(w);

				float a = mRect->GetAlpha();
				a += 0.4f;
				if (a > 200)
					a = 200;
				mRect->SetAlpha(a);

				auto pos = GetPosition();
				if (mCnt < 90)
				{
					pos.y = -250.f;
				}
				else
				{
					pos.y += 6.f;

					if (pos.y > ActorUpdateScope::Bottom - 10.f)
						SetState(GameLib::Actor::State::Dead);
				}
				SetPosition(pos);


				mCnt++;
			}
		}
	}
}