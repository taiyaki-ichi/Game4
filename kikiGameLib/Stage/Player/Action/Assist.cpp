#include"Assist.hpp"
#include"Stage/Player/Player.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/InputState.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"Stage/Draw/RectangleComponent.hpp"

namespace Game
{
	namespace Stage
	{



		ActionAssist::ActionAssist( Player* p)
			:StageActor(p->GetStageScene())
			,mPlayer(p)
			,mCnt(0)
		{

			SetScale(0.05f);

			auto pos = mPlayer->GetPosition();
			pos.y -= 100.f;
			SetPosition(pos);

			mText=new GameLib::TextComponent(this, "Assets/Font/mplus.ttf",100);
			mText->SetText("J");
			mText->SetSize(GameLib::FontSize::Size_32);
			mText->SetAlpha(150);

			float w = 600.f;
			float h = 600.f;
			float d = 150.f;
			mRect1=new RectangleComponent(this, w + d, h + d, GameLib::Color::Black, 150, 98);
			mRect2=new RectangleComponent(this, w, h, GameLib::Color::White, 150, 99);
		}

		ActionAssist::~ActionAssist()
		{
		}

		void ActionAssist::Input(const GameLib::InputState& state)
		{
			if (state.GetState(GameLib::Key::J) == GameLib::ButtonState::Pressed)
				SetState(GameLib::Actor::State::Dead);
		}

		void ActionAssist::UpdateStageActor()
		{
			auto pos = mPlayer->GetPosition();
			pos.y -= 100.f;
			SetPosition(pos);

			float a = mText->GetAlpha();
			if (mCnt < 50)
			{
				a-=2;
			}
			else
			{
				a += 2;
				if (mCnt > 100)
					mCnt = 0;
			}
			mText->SetAlpha(a);
			mRect1->SetAlpha(a);
			mRect2->SetAlpha(a);

			mCnt++;
			
		}

	}
}