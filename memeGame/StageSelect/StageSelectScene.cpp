#include"StageSelectScene.hpp"
#include"SaveData/SaveData.hpp"
#include"Actor/StartIsland.hpp"
#include"Stage/Player/Player.hpp"
#include"Actor/StageIsland.hpp"
#include"GameStage/GameStageScene.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Object/Ground.hpp"
#include"Actor/HowToActor.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"Actor/SaveBox.hpp"

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
			


			new StartIsland(this);

			
			new StageIsland(this, 1, "../Assets/Box/001.png");
			if(SaveData::GetStageData(1)>0)
				new StageIsland(this, 2, "../Assets/Box/002.png");
			if(SaveData::GetStageData(2)>0)
				new StageIsland(this, 3, "../Assets/Box/003.png");

			
			int i = 0;
			float r=0;
			
			while (SaveData::GetStageData(i) > 0&&i<StageNum)
			{
				r = StartIsland::WIDTH + StageIsland::WIDTH * (i + 2);
				SetStageRight(r);
				i++;
			}

			new Stage::Ground(this, GameLib::Vector2(r - StageIsland::WIDTH / 2.f, WINDOW_HEIGHT - 75.f), StageIsland::WIDTH, 150.f);
				
			new Stage::Ground(this, GameLib::Vector2(r + 50, WINDOW_HEIGHT / 2.f), 100.f, WINDOW_HEIGHT);

			new HowTo::Left(this, GameLib::Vector2(StartIsland::WIDTH / 2.f - 90.f, WINDOW_HEIGHT / 2.f - 170.f));
			new HowTo::Right(this, GameLib::Vector2(StartIsland::WIDTH / 2.f + 90.f, WINDOW_HEIGHT / 2.f - 170.f));
			new HowTo::Jump(this, GameLib::Vector2(StartIsland::WIDTH / 2.f, WINDOW_HEIGHT / 2.f - 120.f));

			float w = 300.f;
			float h = 300.f;
			auto ac = new Stage::StageActor(this, GameLib::Vector2(StartIsland::WIDTH / 2.f, WINDOW_HEIGHT / 2.f - 100.f));
			new Stage::RectangleComponent(ac, w + 20.f, h + 20.f, GameLib::Color::Black, 255, -10);
			new Stage::RectangleComponent(ac, w, h, GameLib::Color::White, 255, -5);


			GameLib::Vector2 pPos(GameLib::Vector2(StartIsland::WIDTH / 2.f, WINDOW_HEIGHT - 170.f));
			for (int i = 0; i < playerPos; i++)
			{
				if (i == 0)
					pPos.x += StartIsland::WIDTH / 2.f + StageIsland::WIDTH / 2.f;
				else
					pPos.x += StageIsland::WIDTH;
			}
			new Stage::Player(this, pPos);

		
			new SaveBox(this, GameLib::Vector2(120.f, WINDOW_HEIGHT / 2.f));
		}

		Scene::~Scene()
		{

		}

		GameLib::Scene* Scene::UpdateStageScene()
		{
		
			if (mMoveFlag == 1)
				return new Stage::GameStageScene(1, "../StageData/stage001.json");
			else if(mMoveFlag==2)
				return new Stage::GameStageScene(2, "../StageData/stage002.json");
			else if (mMoveFlag == 3)
				return new Stage::GameStageScene(3, "../StageData/stage003.json");
				

			return this;
		}

	}
}