#include"SaveBox.hpp"
#include"StageSelect/StageSelectScene.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"SaveData/SaveData.hpp"

namespace Game
{
	namespace StageSelect
	{

		SaveBox::SaveBox(Scene* s, const GameLib::Vector2& pos)
			:Stage::StageActor(s,pos)
			,mCnt(-1)
		{
			new Stage::RectangleComponent(this, 70.f, 70.f, GameLib::Color::Black);
			new Stage::Body(this,"Ground", 70.f, 70.f);

			auto text = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf");
			text->SetText("SAVE");
			text->SetAdjust(GameLib::Vector2(0.f, -150.f));

			auto text2 = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf");
			text2->SetText("Бе");
			text2->SetAdjust(GameLib::Vector2(0.f, -100.f));

			mText = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf");
			mText->SetText("OK");
			mText->SetColor(GameLib::Color::White);
			mText->SetAlpha(0);
			
		}

		SaveBox::~SaveBox()
		{
		}

		void SaveBox::UpdateStageActor()
		{
			if (mCnt >= 0)
				mCnt++;

			if (mCnt > 60)
				mCnt = -1;

			float alpha = mText->GetAlpha();
			alpha -= 2.f;
			if (alpha < 0.f)
				alpha = 0.f;
			mText->SetAlpha(alpha);
		}

		void SaveBox::Hit(Stage::Body* myBody, Stage::Body* theBody)
		{
			std::string name = theBody->GetName();
			if (name == "Player" && mCnt < 0)
			{
				mCnt = 0;
				SaveData::Save();
				mText->SetAlpha(255.f);
			}
		}

	}
}