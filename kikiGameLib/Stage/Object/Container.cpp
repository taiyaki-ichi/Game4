#include"Container.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/Enemy/EnemyState.hpp"


namespace Game
{
	namespace Stage
	{

		const float ContainerActive::GRAVITY = 5.f;
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
			, mPlayerPosFlag(0)
		{
		}

		ContainerActive::~ContainerActive()
		{
		}

		StageState* ContainerActive::Update()
		{

			auto pos = mContainer->GetPosition();

			if (mPlayerPosFlag == 1)
				pos.x += SPEED;
			else if (mPlayerPosFlag == -1)
				pos.x -= SPEED;

			if (!mOnGround)
			{
				pos.y += GRAVITY;
			}
			else
			{
				//地面との接触をチェックするため
				pos.y += 0.01f;
			}


			mContainer->SetPosition(pos);
			mOnGround = false;
			mPlayerPosFlag = 0;


			return this;
		}

		void ContainerActive::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Ground")
			{
				GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, SPEED);
				if (adjust.y < 0.f)
					mOnGround = true;
				mContainer->SetPosition(mContainer->GetPosition() + adjust);
			}
			else if (name == "Player")
			{

				GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, SPEED, GRAVITY);
				if (adjust.x > 0.f)
				{
					//くっつかないようにするため少し押し出す
					adjust.x += 0.01f;
					mContainer->SetPosition(mContainer->GetPosition() + adjust);
				}
				else if (adjust.x < 0.f)
				{
					adjust.x -= 0.01f;
					mContainer->SetPosition(mContainer->GetPosition() + adjust);
				}

			}
			else if (name == "Container")
			{
				auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, SPEED, GRAVITY);
				float v = myBody->GetVelocity().x;
				auto myPos = mContainer->GetPosition();
				if (GameLib::Math::Abs(adjust.x) > 0.f)
				{
					//ほかのContainerを押した場合
					if (v * adjust.x < 0.f)
					{
						theBody->GetOwner()->SetPosition(theBody->GetOwner()->GetPosition() - adjust);
					}
					//押された場合は、何もしない

				}
				else if (adjust.y <= 0.f)
				{
					if (adjust.y < 0.f)
						mOnGround = true;

					mContainer->SetPosition(myPos + adjust);
				}
			}
			else if (name == "Beam")
			{
				mContainer->BreakBody();
				mContainer->SetStageState(new Enemy::Fall(mContainer));
			}
		}

}
}
