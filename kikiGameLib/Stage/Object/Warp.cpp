#include"Warp.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/StageScene.hpp"


namespace Game
{
	namespace Stage
	{

		float Warp::SPEED = 20.f;

		Warp::Warp(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
			:StageActor(scene,pos,updateOrder)
			,mTarget(nullptr)
			,mCnt(-1)
			,mPlayer(nullptr)
			,mPlayerBody(nullptr)
		{
			SetScale(0.1f);

			new GameLib::TextureComponent(this, "../Assets/Other/warp.png");

			auto body = new Body(this, "Warp", 500.f, 500.f);
			body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
		}

		Warp::~Warp()
		{
		}

		void Warp::UpdateStageActor()
		{
			SetRotation(GetRotation() + 0.03f);

			if (mCnt > 60)
				mCnt = -1;

			
			if (mCnt >= 0)
				mCnt++;
				
			if (mPlayer)
			{
				auto vec = mTarget->GetPosition() - GetPosition();
				auto playerPos = mPlayer->GetPosition();
				playerPos += GameLib::Vector2::Normalize(vec) * SPEED;

				mPlayer->SetPosition(playerPos);
				mPlayer->SetRotation(mPlayer->GetRotation() + 0.2f);

				float l2 = (playerPos - mTarget->GetPosition()).Length();

				//1.f‚ÍŒë·—p
				//if (l1 + l2 > l+4.f)
				if(l2<50.f)
				{
					mPlayerBody->SetWidthAndHeight(250.f, 500.f);
					mPlayer->SetRotation(0.f);
					mPlayer->SetPosition(mTarget->GetPosition());

					mPlayer = nullptr;
					mPlayerBody = nullptr;

					mTarget->GoPlayer();
				}

			}
		}

		void Warp::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();
			
			if (name == "Player" && !mPlayer && mTarget && mCnt < 0)
			{
				theBody->SetWidthAndHeight(0.f, 0.f);
				mPlayer = theBody->GetStageOwner();
				mPlayerBody = theBody;

				mPlayer->SetPosition(GetPosition());

			}
		}

	}
}