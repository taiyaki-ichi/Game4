#include"StageIsland.hpp"
#include"StageSelect/StageSelectScene.hpp"
#include"SceneMoveBox.hpp"
#include"Stage/Object/Ground.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"SaveData/SaveData.hpp"
#include"StartIsland.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"StageSelectBackGround.hpp"
#include"Stage/Player/Player.hpp"

#include<iostream>

namespace Game
{
	namespace StageSelect
	{

		float StageIsland::WIDTH = 300.f;

		StageIsland::StageIsland(Scene* scene, int stageNum, const std::string& boxFileName)
			:Stage::StageActor(scene)
			, mBackGroundActiveFlag(false)
		{
			float x = StartIsland::WIDTH - WIDTH / 2.f + WIDTH * stageNum;
			GameLib::Vector2 pos(x, WINDOW_HEIGHT / 2.f);
			SetPosition(pos);

			new SceneMoveBox(scene, boxFileName, stageNum, GameLib::Vector2(x, WINDOW_HEIGHT / 2.f));

			new Stage::Ground(scene, GameLib::Vector2(x, WINDOW_HEIGHT - 75.f), WIDTH, 150.f);

			auto text = new GameLib::TextComponent(this, "../Assets/Font/mplus.ttf", 10);
			text->SetAdjust(GameLib::Vector2(0.f, 225.f));
			text->SetColor(GameLib::Color::White);
			text->SetSize(GameLib::FontSize::Size_96);
			text->SetText(std::to_string(stageNum));

			auto text2 = new GameLib::TextComponent(this, "../Assets/Font/mplus.ttf", 10);
			text2->SetAdjust(GameLib::Vector2(0.f, -200.f));
			text2->SetSize(GameLib::FontSize::Size_32);
			text2->SetText("SCORE");


			std::string sc;
			int score = SaveData::GetStageData(stageNum);
			if (score == 1)
				sc = "C";
			else if (score == 2)
				sc = "B";
			else if (score == 3)
				sc = "A";
			else if (score == 4)
				sc = "S";
			else
				sc = "-";

			auto text3 = new GameLib::TextComponent(this, "../Assets/Font/mplus.ttf", 10);
			text3->SetAdjust(GameLib::Vector2(0.f, -130.f));
			text3->SetSize(GameLib::FontSize::Size_96);
			text3->SetText(sc);

			Game::Stage::StageActor* actor;
			GameLib::TextureComponent* texture;

			float l = 60.f;
			float scale = 0.03;

			actor = new Game::Stage::StageActor(scene, GameLib::Vector2(pos.x + l, pos.y - l));
			actor->SetScale(scale);
			texture = new GameLib::TextureComponent(actor, "../Assets/Box/arrow.png");

			actor = new Game::Stage::StageActor(scene, GameLib::Vector2(pos.x - l, pos.y - l));
			actor->SetScale(scale);
			texture = new GameLib::TextureComponent(actor, "../Assets/Box/arrow.png");
			texture->SetTextureFlip(GameLib::TextureFlip::Horizontal);

			actor = new Game::Stage::StageActor(scene, GameLib::Vector2(pos.x + l, pos.y + l));
			actor->SetScale(scale);
			texture = new GameLib::TextureComponent(actor, "../Assets/Box/arrow.png");
			texture->SetTextureFlip(GameLib::TextureFlip::Vertical);

			actor = new Game::Stage::StageActor(scene, GameLib::Vector2(pos.x - l, pos.y + l));
			actor->SetScale(scale);
			actor->SetRotation(GameLib::Math::Pi);
			texture = new GameLib::TextureComponent(actor, "../Assets/Box/arrow.png");


			mBackGroundManager = new BackGroundManager();

			CreateBackGround(this, stageNum);

		}

		StageIsland::~StageIsland()
		{
			if (mBackGroundManager)
				delete mBackGroundManager;
		}

		void StageIsland::UpdateStageActor()
		{
			if (!mBackGroundActiveFlag)
			{
				auto pos = GetPosition();
				auto playerPos = GetStageScene()->GetPlayer()->GetPosition();
				if (GameLib::Math::Abs(pos.x - playerPos.x) < 100.f)
				{
					mBackGroundManager->Active();
					mBackGroundActiveFlag = true;
				}
			}
			else
			{
				auto pos = GetPosition();
				auto playerPos = GetStageScene()->GetPlayer()->GetPosition();
				if (GameLib::Math::Abs(pos.x - playerPos.x) > 150.f)
				{
					mBackGroundManager->Stay();
					mBackGroundActiveFlag = false;
				}
			}
		}

		void StageIsland::AddBackGround(BackGround* b)
		{
			mBackGroundManager->Add(b);
		}

		void CreateBackGround(StageIsland* s, int stageNum)
		{
			if (stageNum == 1)
			{
				for (int i = 0; i < 100; i++)
					new Leaf(s);

				new Horizon130(s);
				new Horizon180(s);
				new Horizon230(s);

				new FixedBackGround(s, "../Assets/BackGround/tree-130.png", GameLib::Vector2(WINDOW_WIDTH / 2.f, 250.f), 0.5f, -50.f, 0.8f);
				new FixedBackGround(s, "../Assets/BackGround/tree-130.png", GameLib::Vector2(WINDOW_WIDTH / 2.f + 400.f, 250.f), 0.5f, -50.f, 0.8f);
				new FixedBackGround(s, "../Assets/BackGround/tree-130.png", GameLib::Vector2(WINDOW_WIDTH / 2.f - 400.f, 250.f), 0.5f, -50.f, 0.8f);

				new FixedBackGround(s, "../Assets/BackGround/tree-180.png", GameLib::Vector2(140.f, 250.f), 0.3f, -60.f, 0.6f);
				new FixedBackGround(s, "../Assets/BackGround/tree-180.png", GameLib::Vector2(330.f, 250.f), 0.3f, -60.f, 0.6f);
				new FixedBackGround(s, "../Assets/BackGround/tree-180.png", GameLib::Vector2(490.f, 250.f), 0.3f, -60.f, 0.6f);
				new FixedBackGround(s, "../Assets/BackGround/tree-180.png", GameLib::Vector2(660.f, 250.f), 0.3f, -60.f, 0.6f);

				new FixedBackGround(s, "../Assets/BackGround/mountain-230.png", GameLib::Vector2(WINDOW_WIDTH / 2.f, 100.f), 0.6f, -70.f, 0.5f);
				new FixedBackGround(s, "../Assets/BackGround/mountain-230.png", GameLib::Vector2(WINDOW_WIDTH / 2.f - 300.f, 100.f), 0.6f, -70.f, 0.5f);
				new FixedBackGround(s, "../Assets/BackGround/mountain-230.png", GameLib::Vector2(WINDOW_WIDTH / 2.f + 300.f, 100.f), 0.6f, -70.f, 0.5f);

			}
		}

	}
}