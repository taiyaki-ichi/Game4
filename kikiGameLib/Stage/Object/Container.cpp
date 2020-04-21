#include"Container.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/Enemy/EnemyState.hpp"
#include"Trampoline.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{

		const float ContainerActive::GRAVITYPOWER = 0.3f;
		const float ContainerActive::SPEED = 2.f;

		Container::Container(StageScene* scene, const GameLib::Vector2& pos, int UupdateOrder)
			:StageStateActor(scene,pos,UupdateOrder)
		{
			SetScale(0.2f);

			mTexture = new GameLib::TextureComponent(this, "../Assets/Other/container.png");

			mBody = new Game::Stage::Body(this, "Container");
			mBody->SetWidthAndHeight(500.f, 500.f);
			mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

			SetStageState(new ContainerActive(this));
		}

		Container::~Container()
		{
		}

		


		void Container::BreakBody()
		{
			mBody->SetWidthAndHeight(0.f, 0.f);
		}

		ContainerActive::ContainerActive(Container* contaner)
			:StageState()
			,mContainer(contaner)
			, mOnGround(false)
			,mGroundTimeCnt(-1)
			,mVelocityY(0.f)
		{
		}

		ContainerActive::~ContainerActive()
		{
		}

		StageState* ContainerActive::Update()
		{

			auto pos = mContainer->GetPosition();

			if (!mOnGround)
			{
				//pos.y += GRAVITY;
				mVelocityY += GRAVITYPOWER;
			}
			else
			{
				//地面との接触をチェックするため
				mVelocityY += 0.01;
				//pos.y += 0.01f;
			}

			pos.y += mVelocityY;
			mContainer->SetPosition(pos);
			mOnGround = false;

		
			
			if (mGroundTimeCnt > 0)
				mGroundTimeCnt--;

			if (mGroundTimeCnt == 0)
			{
				mContainer->GetBody()->SetName("Container");
				mGroundTimeCnt = -1;
			}

			return this;
		}

		void ContainerActive::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();
			std::string myName = myBody->GetName();

			if (name == "Ground")
			{
				GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, 0.f, SPEED);
				if (adjust.y < 0.f)
				{
					mOnGround = true;
					mVelocityY = 0.f;
					adjust.x += theBody->GetVelocity().x;
				}
				else if (GameLib::Math::Abs(adjust.x) > 0.f&&myBody->GetVelocity().y==0.f)
				{
					mGroundTimeCnt = 60;
					if (myName != "Ground")
					{
						myBody->SetName("Ground");
					}
				}
				
				mContainer->SetPosition(mContainer->GetPosition() + adjust);
			}
			else if (name == "Container" && myName != "Ground")
			{
				auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, 0.f,SPEED);

				float theV= theBody->GetVelocity().x;
				if (adjust.y < 0.f)
				{
					mOnGround = true;
					adjust.x += theV;
					mVelocityY = 0.f;
					mContainer->SetPosition(mContainer->GetPosition() + adjust);
				}
				else if (theV * adjust.x > 0.f)
				{
					mContainer->SetPosition(mContainer->GetPosition() + adjust);
				}
				
			}
			else if (name == "Beam")
			{
				mContainer->BreakBody();
				mContainer->SetStageState(new Enemy::Fall(mContainer));
			}
			else if(name == "Trampoline")
			{
				GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, 0.f, SPEED);
				if (adjust.y < 0.f)
				{
					mOnGround = true;
					mVelocityY = -15.f;
				}
				else if (GameLib::Math::Abs(adjust.x) > 0.f && myBody->GetVelocity().y == 0.f)
				{
					mGroundTimeCnt = 60;
					if (myName != "Ground")
					{
						myBody->SetName("Ground");
					}
				}

				mContainer->SetPosition(mContainer->GetPosition() + adjust);
			}
		}

}
}
