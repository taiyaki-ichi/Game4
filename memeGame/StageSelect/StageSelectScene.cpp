#include"StageSelectScene.hpp"
#include"SaveData/SaveData.hpp"
#include"Actor/StartIsland.hpp"
#include"Stage/Player/Player.hpp"
#include"Actor/StageIsland.hpp"
#include"GameStage/GameStageScene.hpp"
#include"Stage/CollisionDetection/Body.hpp"

#include<iostream>

namespace Game
{
	namespace StageSelect
	{
		Scene::Scene(int playerPos)
			:Stage::StageScene()
			,mMoveFlag(0)
		{
			Game::Stage::Body::SetDrawFlag(false);

			SaveData::SetStageData(0, 1);
			GameLib::Vector2 pPos(GameLib::Vector2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 200.f));
			for (int i = 0; i < playerPos; i++)
			{
				if (i == 0)
					pPos.x += WINDOW_WIDTH / 2.f + StageIsland::WIDTH / 2.f;
				else
					pPos.x += StageIsland::WIDTH;
			}
			new Stage::Player(this, pPos);


			new StartIsland(this);

			
			new StageIsland(this, 1, "../Assets/Box/001.png");
			if(SaveData::GetStageData(1)>0)
				new StageIsland(this, 2, "../Assets/Box/001.png");
			if(SaveData::GetStageData(2)>0)
				new StageIsland(this, 3, "../Assets/Box/001.png");

		}

		Scene::~Scene()
		{

		}

		GameLib::Scene* Scene::UpdateStageScene()
		{
			if (mMoveFlag == 1)
				return new Stage::GameStageScene(1, "../StageData/stage002.json");
			else if(mMoveFlag==2)
				return new Stage::GameStageScene(2, "../StageData/stage002.json");
			else if (mMoveFlag == 3)
				return new Stage::GameStageScene(3, "../StageData/stage002.json");


			return this;
		}

	}
}