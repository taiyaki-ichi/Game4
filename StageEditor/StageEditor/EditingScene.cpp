#include"EditingScene.hpp"
#include"lib/include/Actor.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"lib/include/InputState.hpp"
#include"Cursor.hpp"
#include"EditingActor.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include <fstream>
#include <sstream>
#include"picojson/picojson.hpp"
#include"CommandActor.hpp"

namespace StageEditor
{
	using Vec2 = GameLib::Vector2;


	EditingScene::EditingScene()
		:Game::Stage::StageScene()
		,mScreemMoveSum(0.f,0.f)
	{
		
		mCursor = new Cursor(this);
		mCommandActor = new CommandActor(this);

		LoadEditingData(this,"Data/test");

		Game::Stage::Body::SetDrawFlag(true);
	}
	EditingScene::~EditingScene()
	{
	}

	void EditingScene::Input(const GameLib::InputState& state)
	{

		Vec2 ad(0.f, 0.f);
		if (state.GetState(GameLib::Key::Right) == GameLib::ButtonState::Pressed)
			ad = Vec2(50.f, 0.f);
		else if (state.GetState(GameLib::Key::Left) == GameLib::ButtonState::Pressed)
			ad = Vec2(-50.f, 0.f);
		else if (state.GetState(GameLib::Key::Up) == GameLib::ButtonState::Pressed)
			ad = Vec2(0.f, -50.f);
		else if (state.GetState(GameLib::Key::Down) == GameLib::ButtonState::Pressed)
			ad = Vec2(0.f, 50.f);
		else if (state.GetState(GameLib::Key::Right) == GameLib::ButtonState::Held)
			ad = Vec2(5.f, 0.f);
		else if (state.GetState(GameLib::Key::Left) == GameLib::ButtonState::Held)
			ad = Vec2(-5.f, 0.f);
		else if (state.GetState(GameLib::Key::Up) == GameLib::ButtonState::Held)
			ad = Vec2(0.f, -5.f);
		else if (state.GetState(GameLib::Key::Down) == GameLib::ButtonState::Held)
			ad = Vec2(0.f, 5.f);



		mScreemMoveSum += ad;
		MoveScreen(ad);
	}

	GameLib::Scene* EditingScene::UpdateStageScene()
	{
		if (mCommandActor->GetCheckFlag())
		{
			CreateJsonData(mEditingActors, "Data/test.json", mScreemMoveSum);
			return new CheckScene();
		}
		
		if (mCommandActor->GetSaveFlag())
		{
			std::string name = mCommandActor->GetText().substr(6);
			CreateJsonData(mEditingActors, "../StageData/" + name + ".json", mScreemMoveSum);
			mCommandActor->SaveComplete();
		}

		if (mCommandActor->GetLoadFlag())
		{
			std::string name = mCommandActor->GetText().substr(4);
			LoadStageData(name);
			mCommandActor->LoadComplete();
		}

		return this;
	}

	void EditingScene::AddEditingActor(EditingActor* actor)
	{
		auto iter = std::find(mEditingActors.begin(), mEditingActors.end(), actor);
		if (iter == mEditingActors.end())
			mEditingActors.emplace_back(actor);
	}

	void EditingScene::RemoveEditingActor(EditingActor* actor)
	{
		auto iter = std::find(mEditingActors.begin(), mEditingActors.end(), actor);
		if (iter != mEditingActors.end())
			mEditingActors.erase(iter);
	}

	void EditingScene::Reset()
	{
		ResetEditingActors();
		ResetScreemMoveSum();
	}

	void EditingScene::LoadStageData(const std::string& fileName)
	{
		Reset();

		LoadEditingData(this, "../StageData/" + fileName);

	}

	void EditingScene::ResetEditingActors()
	{
		while (!mEditingActors.empty())
			delete mEditingActors.back();
		mEditingActors.clear();
	}

	void EditingScene::ResetScreemMoveSum()
	{
		mScreemMoveSum = Vec2(0.f, 0.f);
	}

	const GameLib::Vector2& EditingScene::GetCursorPos() const
	{
		return mCursor->GetPosition();
	}
	

	bool CreateJsonData(std::vector<EditingActor*>& actors, const std::string& fileName, const GameLib::Vector2& adjust)
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
				if (i % 2 == 0)
					jsonData.insert(std::make_pair(dataStr + std::to_string(i + 1), picojson::value(data.at(i) + adjust.x)));
				else
					jsonData.insert(std::make_pair(dataStr + std::to_string(i + 1), picojson::value(data.at(i) + adjust.y)));
			}

			jsonArry.push_back(picojson::value(jsonData));
			jsonData.clear();
		}

		picojson::object all;
		all.insert(std::make_pair("Actors", picojson::value(jsonArry)));

		std::ofstream ofs(fileName);
		ofs << picojson::value(all).serialize(true) << std::endl;

		return true;
	}


	CheckScene::CheckScene()
		:Game::Stage::StageScene()
		,mBackFlag(false)
	{
		Game::Stage::LoadStageData(this, "Data/test.json");
		Game::Stage::Body::SetDrawFlag(true);
	}

	CheckScene::~CheckScene()
	{
	}

	void CheckScene::Input(const GameLib::InputState& state)
	{
		mBackFlag = state.GetState(GameLib::Key::BackSpace) == GameLib::ButtonState::Pressed;
	}

	GameLib::Scene* CheckScene::UpdateStageScene()
	{
		if (mBackFlag)
			return new EditingScene();
		else
			return this;
	}



	bool LoadEditingData(EditingScene* scene, const std::string& fileName)
	{
		using Vec2 = GameLib::Vector2;

		// JSONデータの読み込み。

		std::ifstream ifs(fileName + ".json", std::ios::in);
		if (ifs.fail()) {
			std::cerr << "failed to read " << fileName << ".json" << std::endl;
			return false;
		}

		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		picojson::value v;
		const std::string err = picojson::parse(v, json);
		if (err.empty() == false) {
			std::cerr << err << std::endl;
			return false;
		}

		picojson::object& obj = v.get<picojson::object>();
		picojson::array& ary = obj["Actors"].get<picojson::array>();

		EditingActor* actor=nullptr;
		double x, y;
		for (const auto& e : ary)
		{
			picojson::object o = e.get<picojson::object>();

			x = o["Data1"].get<double>();
			y = o["Data2"].get<double>();

			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//ここに追加
			/////////////////////////////////////////////////////////////////////////////////////////////////////


			if (o["Name"].get<std::string>() == "Player")
			{
				actor = new EditingPlayer(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "Ground")
			{
				actor = new EditingGround(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "Triple")
			{
				actor = new EditingTriple(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "Toge")
			{
				actor = new EditingToge(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "Frog")
			{
				actor = new EditingFrog(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "StraightBee")
			{
				actor = new EditingStraightBee(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "CircleBee")
			{
				actor = new EditingCircleBee(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "ItemCock")
			{
				actor = new EditingItemCock(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "ItemWizard")
			{
				actor = new EditingItemWizard(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "ItemAlien")
			{
				actor = new EditingItemAlien(scene, Vec2(x, y));
			}
			


			if (actor)
			{
				for (int i = 0; i < actor->GetDataNum(); i++)
				{
					actor->AddData(o["Data" + std::to_string(i + 1)].get<double>());
				}
				scene->AddEditingActor(actor);
			}
			actor = nullptr;

		}

		return true;

	}



}