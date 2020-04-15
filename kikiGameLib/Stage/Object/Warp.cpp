#include"Warp.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/StageScene.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{

		Warp::Warp(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
			:StageActor(scene,pos,updateOrder)
			,mTarget(nullptr)
			,mCnt(-1)
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

			if (mCnt > 120)
				mCnt = -1;

			
			if (mCnt >= 0)
				mCnt++;
				
		}

		void Warp::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();
			
			if (name == "Player" && mCnt < 0 && mTarget)
			{
				theBody->GetOwner()->SetPosition(mTarget->GetPosition());
				mTarget->GoPlayer();

			}
		}

	}
}