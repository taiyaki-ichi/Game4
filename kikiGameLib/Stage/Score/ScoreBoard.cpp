#include"ScoreBoard.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"WindowData.hpp"
#include"lib/include/Draw/LineComponent.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/StageScene.hpp"
#include"lib/include/Draw/TextComponent.hpp"

namespace Game
{
	namespace Stage
	{
		ScoreBoard::ScoreBoard(StageScene* scene)
			:StageActor(scene)
			,mCnt(0)
		{
			GameLib::Vector2 center(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - 100.f);
			float width = 300.f;
			float height = 300.f;

			SetPosition(center);
			new RectangleComponent(this, width+20.f, height+20.f, GameLib::Color::Black, 255, 9998);
			new RectangleComponent(this, width, height, GameLib::Color::White, 255, 9999);

			auto line=new GameLib::LineComponent(this,10000);
			line->SetPoints(GameLib::Vector2(WINDOW_WIDTH / 2.f - width / 2.f, WINDOW_HEIGHT / 2.f - 50.f), GameLib::Vector2(WINDOW_WIDTH / 2.f + width / 2.f, WINDOW_HEIGHT / 2.f - 50.f));
		
			auto a1 = new StageActor(scene, center + GameLib::Vector2(-width / 2.f+30.f, -100.f));
			a1->SetScale(0.1f);
			new GameLib::TextureComponent(a1, "../Assets/Item/diamond02.png", 10000);

			auto a2 = new StageActor(scene, center + GameLib::Vector2(-width / 2.f+30.f, 0.f));
			a2->SetScale(0.1f);
			new GameLib::TextureComponent(a2, "../Assets/Item/tear.png", 10000);

			auto t1 = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
			t1->SetText("~");
			t1->SetAdjust(GameLib::Vector2(-width / 3.f+40.f, -100.f));

			auto t2 = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
			t2->SetText("~");
			t2->SetAdjust(GameLib::Vector2(-width / 3.f + 40.f, 0.f));

			auto t3 = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
			t3->SetText("/30");
			t3->SetAdjust(GameLib::Vector2(width / 2.f - 50.f, -100.f));

			auto t4 = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
			t4->SetText("/3");
			t4->SetAdjust(GameLib::Vector2(width / 2.f - 50.f, 0.f));

			
			auto t5 = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
			t5->SetText("SCORE");
			t5->SetAdjust(GameLib::Vector2(-width / 2.f + 30.f, 100.f));
			t5->SetSize(GameLib::FontSize::Size_16);

			


		}
		ScoreBoard::~ScoreBoard()
		{
		}
		void ScoreBoard::UpdateStageActor()
		{
			if (mCnt == 40)
			{
				auto t = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
				t->SetText(std::to_string(GetStageScene()->GetDiamondNum()));
				t->SetAdjust(GameLib::Vector2(10.f, -100.f));
			}

			if (mCnt == 80)
			{
				auto t = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
				t->SetText(std::to_string(GetStageScene()->GetTearNum()));
				t->SetAdjust(GameLib::Vector2(10.f, 0.f));
			}

			if (mCnt == 140)
			{
				int sum = GetStageScene()->GetDiamondNum() + GetStageScene()->GetTearNum() * 5;
				std::string score = "C";
				if (15 <= sum && sum < 30)
					score = "B";
				else if (30 <= sum && sum < 45)
					score = "A";
				else if (sum == 45)
					score = "S";

				auto t = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 10000);
				t->SetText(score);
				t->SetAdjust(GameLib::Vector2(10.f, 100.f));
			}

			if (mCnt > 200)
				GetStageScene()->StageClear();

			mCnt++;
		}
	}
}