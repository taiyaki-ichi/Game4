#include"CommandActor.hpp"
#include"EditingScene.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"lib/include/InputState.hpp"
#include"EditingActor.hpp"

#include<iostream>

namespace StageEditor
{
	using Vec2 = GameLib::Vector2;


	CommandActor::CommandActor(EditingScene* scene)
		:GameLib::Actor(scene,-100)
		,mNowEditingActor(nullptr)
		,mEditingScene(scene)
		,mCheckFlag(false)
		,mSaveFlag(false)
		,mLoadFlag(false)
	{
		SetPosition(Vec2(WINDOW_WIDTH / 2.f, 16.f));

		mTextComponent = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf",100);
		mTextComponent->SetColor(GameLib::Color::Black);
		mTextComponent->SetAlpha(200);
		mTextComponent->SetSize(GameLib::FontSize::Size_32);
		mTextComponent->SetText("");

	}

	CommandActor::~CommandActor()
	{
	}

	void CommandActor::Input(const GameLib::InputState& state)
	{

		if (mNowEditingActor)
		{
			if (mNowEditingActor->IsOk())
			{
				mEditingScene->AddEditingActor(mNowEditingActor);
				mNowEditingActor = nullptr;
			}
		}
		else
		{

			std::string text = mTextComponent->GetText();
			if (state.GetState(GameLib::Key::BackSpace) == GameLib::ButtonState::Pressed && text.size() > 0)
				text.pop_back();
			else
				text += GetKey(state);
			mTextComponent->SetText(text);

			bool enter = state.GetState(GameLib::Key::Enter) == GameLib::ButtonState::Pressed;
			Vec2 cursorPos = state.GetMousePos();
			EvaluateTextAndEnter(enter,cursorPos);

		}
	}

	void CommandActor::Update()
	{

	}

	const std::string& CommandActor::GetText() const
	{
		return mTextComponent->GetText();
	}

	void CommandActor::EvaluateTextAndEnter(bool enter,  const GameLib::Vector2& cursorPos)
	{
		GameLib::Vector3 color = GameLib::Color::Black;
		std::string text = mTextComponent->GetText();

		std::string s = "saveas";
		bool saveas = false;
		if (text.size() >= 6)
			saveas = std::equal(s.begin(), s.end(), text.begin());
			
		std::string l = "load";
		bool load = false;
		if (text.size() >= 4)
			load = std::equal(l.begin(), l.end(), text.begin());

		if (text == "check")
		{
			color = GameLib::Color::Blue;
			if (enter)
				mCheckFlag = true;
		}
		else if (saveas)
		{
			color = GameLib::Color::Blue;
			if (enter)
			{
				mSaveFlag = true;
			}
		}
		else if (text == "reset")
		{
			color = GameLib::Color::Blue;
			if (enter)
				mEditingScene->Reset();
		}
		else if (load)
		{
			color = GameLib::Color::Blue;
			if (enter)
			{
				mLoadFlag = true;
			}
		}
		else if (text == "switchdraw")
		{
			color = GameLib::Color::Blue;
			if (enter)
				mEditingScene->SwitchDrawFlag();
		}

		else if (text == "player")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingPlayer(mEditingScene, cursorPos);
		}
		else if (text == "ground")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingGround(mEditingScene, cursorPos);

		}
		else if (text == "triple")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingTriple(mEditingScene, cursorPos);

		}
		else if (text == "toge")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingToge(mEditingScene, cursorPos);
		}
		else if (text == "frog")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingFrog(mEditingScene, cursorPos);
		}
		else if (text == "straightbee")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingStraightBee(mEditingScene, cursorPos);
		}
		else if (text == "circlebee")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingCircleBee(mEditingScene, cursorPos);
		}
		else if (text == "itemcock")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingItemCock(mEditingScene, cursorPos);
		}
		else if (text == "itemwizard")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingItemWizard(mEditingScene, cursorPos);
		}
		else if (text == "itemalien")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingItemAlien(mEditingScene, cursorPos);
		}
		else if (text == "container")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingContainer(mEditingScene, cursorPos);
		}
		else if (text == "moveground")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingMoveGround(mEditingScene, cursorPos);
		}
		else if (text == "diamond")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingDiamond(mEditingScene, cursorPos);
		}
		else if (text == "standlight")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingStandLight(mEditingScene, cursorPos);
		}
		else if (text == "carrot")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingCarrot(mEditingScene, cursorPos);
		}
		else if (text == "dogu")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingDogu(mEditingScene, cursorPos);
		}
		else if (text == "heart")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingHeart(mEditingScene, cursorPos);
		}
		else if (text == "warp")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingWarp(mEditingScene, cursorPos);
		}
		else if (text == "goal")
		{
			color = GameLib::Color::Red;
			if (enter)
				mNowEditingActor = new EditingGoal(mEditingScene, cursorPos);
		}
		

		mTextComponent->SetColor(color);

	}



	std::string GetKey(const GameLib::InputState& state)
	{
		using k = GameLib::Key;
		using s = GameLib::ButtonState;
		if (state.GetState(k::A) == s::Pressed)
			return "a";
		else if (state.GetState(k::B) == s::Pressed)
			return "b";
		else if (state.GetState(k::C) == s::Pressed)
			return "c";
		else if (state.GetState(k::D) == s::Pressed)
			return "d";
		else if (state.GetState(k::E) == s::Pressed)
			return "e";
		else if (state.GetState(k::F) == s::Pressed)
			return "f";
		else if (state.GetState(k::G) == s::Pressed)
			return "g";
		else if (state.GetState(k::H) == s::Pressed)
			return "h";
		else if (state.GetState(k::I) == s::Pressed)
			return "i";
		else if (state.GetState(k::J) == s::Pressed)
			return "j";
		else if (state.GetState(k::K) == s::Pressed)
			return "k";
		else if (state.GetState(k::L) == s::Pressed)
			return "l";
		else if (state.GetState(k::M) == s::Pressed)
			return "m";
		else if (state.GetState(k::N) == s::Pressed)
			return "n";
		else if (state.GetState(k::O) == s::Pressed)
			return "o";
		else if (state.GetState(k::P) == s::Pressed)
			return "p";
		else if (state.GetState(k::Q) == s::Pressed)
			return "q";
		else if (state.GetState(k::R) == s::Pressed)
			return "r";
		else if (state.GetState(k::S) == s::Pressed)
			return "s";
		else if (state.GetState(k::T) == s::Pressed)
			return "t";
		else if (state.GetState(k::U) == s::Pressed)
			return "u";
		else if (state.GetState(k::V) == s::Pressed)
			return "v";
		else if (state.GetState(k::W) == s::Pressed)
			return "w";
		else if (state.GetState(k::X) == s::Pressed)
			return "x";
		else if (state.GetState(k::Y) == s::Pressed)
			return "y";
		else if (state.GetState(k::Z) == s::Pressed)
			return "z";
		else if (state.GetState(k::Space) == s::Pressed)
			return " ";
		else if (state.GetState(k::no1) == s::Pressed)
			return "1";
		else if (state.GetState(k::no2) == s::Pressed)
			return "2";
		else if (state.GetState(k::no3) == s::Pressed)
			return "3";
		else if (state.GetState(k::no4) == s::Pressed)
			return "4";
		else if (state.GetState(k::no5) == s::Pressed)
			return "5";
		else if (state.GetState(k::no6) == s::Pressed)
			return "6";
		else if (state.GetState(k::no7) == s::Pressed)
			return "7";
		else if (state.GetState(k::no8) == s::Pressed)
			return "8";
		else if (state.GetState(k::no9) == s::Pressed)
			return "9";
		else if (state.GetState(k::no0) == s::Pressed)
			return "0";
		else if (state.GetState(k::Period) == s::Pressed)
			return ".";
		else if (state.GetState(k::Comma) == s::Pressed)
			return ",";
		else
			return "";


	}


}