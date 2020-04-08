#include"StageScene.hpp"
#include"Stage/CollisionDetection/Manager.hpp"
#include"include/Math.hpp"
#include"Player.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{

		StageScene::StageScene()
			:GameLib::Scene()
			,mStageLeft(0.f)
			,mStageRight(2400.f)
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

			AdjustScreen();

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

		void StageScene::AdjustScreen()
		{

			using Vec2 = GameLib::Vector2;
			if (mPlayer)
			{
				Vec2 playerPos = mPlayer->GetPosition();

				if (mStageRight - mStageLeft > WINDOW_WIDTH)
				{
					Vec2 adjust = Vec2(0.f, 0.f);
					
					//さらにスクリーンが端にない時
					if (playerPos.x - mStageLeft > WINDOW_WIDTH / 2.f && mStageRight - playerPos.x > WINDOW_WIDTH / 2.f)
					{
						adjust.x = playerPos.x - Game::WINDOW_WIDTH / 2.f;
						playerPos.x = Game::WINDOW_WIDTH / 2.f;
					}
					MoveScreen(adjust);
					mPlayer->SetPosition(playerPos);
				}
			}
		}

		void StageScene::MoveScreen(const GameLib::Vector2& vec)
		{
			for (auto& actor : mStageActors)
			{
				actor->AdjustPos(-1.f * vec);
			}

			mStageLeft -= vec.x;
			mStageRight -= vec.x;

		}

	}

		
}