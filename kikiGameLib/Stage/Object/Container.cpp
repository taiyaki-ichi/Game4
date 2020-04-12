#include"Container.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextureComponent.hpp"

namespace Game
{
	namespace Stage
	{
		const float Container::GRAVITY = 5.f;
		const float Container::SPEED = 2.f;


		Container::Container(StageScene* scene, const GameLib::Vector2& pos, int UupdateOrder)
			:StageActor(scene,pos,UupdateOrder)
			,mOnGround(false)
			,mPlayerPosFlag(0)
		{
			SetScale(0.2f);

			mTexture = new GameLib::TextureComponent(this, "../Assets/Other/container.png");

			mBody = new Game::Stage::Body(this, "Container");
			mBody->SetWidthAndHeight(500.f, 500.f);
			mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
		}

		Container::~Container()
		{
		}

		void Container::UpdateStageActor()
		{
			auto pos = GetPosition();

			if (mPlayerPosFlag == 1)
				pos.x += SPEED;
			else if (mPlayerPosFlag == -1)
				pos.x -= SPEED;

			if (!mOnGround)
			{
				pos.y += GRAVITY;
			}

			SetPosition(pos);
			mOnGround = false;
			mPlayerPosFlag = 0;
			
		}

		void Container::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Ground" || name == "Container")
			{
				GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, SPEED);
				if (adjust.y < 0.f)
				{
					/*
					if (name == "Container")
						adjust.x += theBody->GetVelocity().x;
					else
						adjust += theBody->GetVelocity();
						*/
					mOnGround = true;

				}
				SetPosition(GetPosition() + adjust);
			}
			else if (name == "Player")
			{
				
				GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, SPEED, GRAVITY);
				if (adjust.x > 0.f)
				{
					adjust.x += 0.01f;
					SetPosition(GetPosition() + adjust);
				}
				else if (adjust.x < 0.f)
				{
					adjust.x -= 0.01f;
					SetPosition(GetPosition() + adjust);
				}
				
			}
		}

	}
}
