#include"EditingScene.hpp"
#include"lib/include/Actor.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"lib/include/Math.hpp"
#include"lib/include/InputState.hpp"
#include"Cursor.hpp"
#include"EditingActor.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include <fstream>
#include <sstream>
#include"picojson/picojson.hpp"

namespace StageEditor
{
	using Vec2 = GameLib::Vector2;


	EditingScene::EditingScene()
		:Game::Stage::StageScene()
		,mCurrEditingActor(nullptr)
		,mGoFlag(false)
	{
		auto actor = new GameLib::Actor(this);
		actor->SetPosition(Vec2(Game::WINDOW_WIDTH / 2.f, -5.f));
		mText = new GameLib::TextComponent(actor,"Assets/Font/mplus.ttf");
		mText->SetColor(GameLib::Color::Black);
		mText->SetAlpha(200);
		mText->SetSize(GameLib::FontSize::Size_32);
		mText->SetText("aaa");

		mCursor = new Cursor(this);
	}
	EditingScene::~EditingScene()
	{
	}

	void EditingScene::Input(const GameLib::InputState& state)
	{
		std::string text = mText->GetText();
		if (state.GetState(GameLib::Key::BackSpace) == GameLib::ButtonState::Pressed && text.size() > 0)
			text.pop_back();
		else
			text += GetKey(state);
		mText->SetText(text);

		bool enter = state.GetState(GameLib::Key::Enter) == GameLib::ButtonState::Pressed;
		if (text == "player")
		{
			mText->SetColor(GameLib::Color::Red);
			if (enter&&!mCurrEditingActor)
				new EditingPlayer(this,mCursor->GetPosition());
			
		}
		else if (text == "ground")
		{
			mText->SetColor(GameLib::Color::Red);
			if (enter&&!mCurrEditingActor)
				new EditingGround(this, mCursor->GetPosition());
		}
		else if (text == "go")
		{
			mText->SetColor(GameLib::Color::Blue);
			if (enter)
			{
				CreateJsonData(mEditingActors, "test");
				mGoFlag = true;
			}
		}
		else
			mText->SetColor(GameLib::Color::Black);
			
	}

	GameLib::Scene* EditingScene::UpdateStageScene()
	{
		if (mGoFlag)
			return new CheckScene();
		
		return this;
	}

	bool EditingScene::AddEditingActor(EditingActor* actor)
	{
		auto iter = std::find(mEditingActors.begin(), mEditingActors.end(), actor);
		if (iter == mEditingActors.end())
		{
			mEditingActors.emplace_back(actor);
		}
		else
			return false;
	}

	void EditingScene::RemoveEditingActor(EditingActor* actor)
	{
		auto iter = std::find(mEditingActors.begin(), mEditingActors.end(), actor);
		if (iter != mEditingActors.end())
			mEditingActors.erase(iter);
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
		else
			return "";


	}

	bool CreateJsonData(std::vector<EditingActor*>& actors, const std::string& fileName)
	{
		picojson::array jsonArry;
		picojson::object jsonData;

		std::cout << "ActorsNum :" << actors.size() << "\n";

		for (auto a : actors)
		{
			
			jsonData.insert(std::make_pair("Name", a->GetName()));

			std::vector<double> data = a->GetDatas();
			std::string dataStr = "Data";
			for (int i = 0; i < data.size(); i++)
			{
				jsonData.insert(std::make_pair(dataStr + std::to_string(i + 1), picojson::value(data.at(i))));
			}

			jsonArry.push_back(picojson::value(jsonData));
			jsonData.clear();
		}

		picojson::object all;
		all.insert(std::make_pair("Actors", picojson::value(jsonArry)));

		std::ofstream ofs("Data/" + fileName + ".json");
		ofs << picojson::value(all).serialize(true) << std::endl;
	}

	CheckScene::CheckScene()
		:Game::Stage::StageScene()
	{
		Game::Stage::LoadStageData(this, "Data/test.json");
		Game::Stage::Body::SetDrawFlag(false);
	}

	CheckScene::~CheckScene()
	{
	}

}