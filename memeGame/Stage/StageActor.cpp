#include"StageActor.hpp"
#include"StageScene.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{

		StageActor::StageActor(StageScene* scene, int updateOrder)
			:GameLib::Actor(scene, updateOrder)
			, mRelativeMoveRate(1.f)
			, mStageScene(scene)
		{
			scene->AddStageActor(this);
		}
		StageActor::StageActor(StageScene* scene, const GameLib::Vector2& vec, int updateOrder)
			:StageActor(scene, updateOrder)
		{
			SetPosition(vec);

		}

		StageActor::~StageActor()
		{
			mStageScene->RemoveStageActor(this);
		}

		void StageActor::Update()
		{
			auto pos = GetPosition();
			//pos‚É‚æ‚Á‚ÄUpdateStageActor‚·‚é‚©‚Ç‚¤‚©

			//
			UpdateStageActor();

		}

		void StageActor::UpdateStageActor()
		{
		}

		void StageActor::AdjustPos(const GameLib::Vector2& vec)
		{
			auto pos = GetPosition();
			pos += vec * mRelativeMoveRate;
			SetPosition(pos);

			AdjustPosSub(vec);
		}

		void StageActor::AdjustPosSub(const GameLib::Vector2& vec)
		{
		}

		void StageActor::Hit(Body* myBody, Body* theBody)
		{
		}
	}
}