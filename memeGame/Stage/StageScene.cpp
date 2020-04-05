#include"StageScene.hpp"
#include"Stage/CollisionDetection/Manager.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{

		StageScene::StageScene()
			:GameLib::Scene()
		{
			mTree = new Liner4Tree(TREELEVEL,
				CollisionDetectionScope::Left, CollisionDetectionScope::Top, CollisionDetectionScope::Right, CollisionDetectionScope::Bottom);
	
			if (!mTree)
				std::cout << "nullptr\n";
		}

		StageScene::~StageScene()
		{
			if (mTree)
				delete mTree;
		}

		GameLib::Scene* StageScene::Update()
		{
			auto next = UpdateStageScene();
			if (mTree)
				mTree->SearchCellArray();

			return next;
		}

		GameLib::Scene* StageScene::UpdateStageScene()
		{
			return this;
		}

		void StageScene::AddStageActor(StageActor* actor)
		{
			mStageActors.emplace_back(actor);
		}

		void StageScene::RemoveStageActor(StageActor* actor)
		{
			auto iter = std::find(mStageActors.begin(), mStageActors.end(), actor);
			if (iter != mStageActors.end())
			{
				mStageActors.erase(iter);
			}
		}

	}
}