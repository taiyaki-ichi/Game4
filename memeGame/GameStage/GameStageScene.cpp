#include"GameStageScene.hpp"
#include"StageSelect/StageSelectScene.hpp"
#include"SaveData/SaveData.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include<iostream>

namespace Game
{
	namespace Stage
	{



		GameStageScene::GameStageScene(int stageNum, const std::string& fileName)
			:Stage::StageScene()
			,mStageNum(stageNum)
		{
			Game::Stage::Body::SetDrawFlag(false);
			LoadStageData(this, fileName);
		}

		GameStageScene::~GameStageScene()
		{
		}

		GameLib::Scene* GameStageScene::UpdateStageScene()
		{

			if (GetPlayerDeathFlag())
				return new StageSelect::Scene(mStageNum);

			if (GetStageClearFlag())
			{
				int sum =GetDiamondNum() + GetTearNum() * 5;
				int score = 1;
				if (15 <= sum && sum < 30)
					score = 2;
				else if (30 <= sum && sum < 45)
					score = 3;
				else if (sum == 45)
					score = 4;

				//std::cout << "GameStageScene Score : " << score << "\n";
				SaveData::SetStageData(mStageNum, score);

				return new StageSelect::Scene(mStageNum);
			}

			return this;
		}

	}
}