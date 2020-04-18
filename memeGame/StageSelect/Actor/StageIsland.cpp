#include"StageIsland.hpp"
#include"StageSelect/StageSelectScene.hpp"
#include"SceneMoveBox.hpp"
#include"Stage/Object/Ground.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"SaveData/SaveData.hpp"
#include"StartIsland.hpp"
#include"lib/include/Draw/TextureComponent.hpp"

#include<iostream>

namespace Game
{
	namespace StageSelect
	{

		float StageIsland::WIDTH = 300.f;

		StageIsland::StageIsland(Scene* scene, int stageNum, const std::string& boxFileName)
			:Stage::StageActor(scene)
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
				sc == "S";
			else
				sc = "-";

			//std::cout << "stageIsland Score :" << score << "\n";

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
			

		}

		StageIsland::~StageIsland()
		{
		}

	}
}