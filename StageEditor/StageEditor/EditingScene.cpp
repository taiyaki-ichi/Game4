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
#include"CommandActor.hpp"

namespace StageEditor
{
	using Vec2 = GameLib::Vector2;


	EditingScene::EditingScene()
		:Game::Stage::StageScene()
	{
		
		mCursor = new Cursor(this);
		mCommandActor = new CommandActor(this);

		LoadEditingData(this);

		Game::Stage::Body::SetDrawFlag(true);
	}
	EditingScene::~EditingScene()
	{
	}

	GameLib::Scene* EditingScene::UpdateStageScene()
	{
		if (mCommandActor->GetChecFlag())
		{
			CreateJsonData(mEditingActors, "test");
			return new CheckScene();
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

	void EditingScene::ResetEditingActors()
	{
		while (!mEditingActors.empty())
			delete mEditingActors.back();
		mEditingActors.clear();
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

		return true;
	}


	CheckScene::CheckScene()
		:Game::Stage::StageScene()
		,mBackFlag(false)
	{
		Game::Stage::LoadStageData(this, "Data/test.json");
		Game::Stage::Body::SetDrawFlag(false);
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



	bool LoadEditingData(EditingScene* scene)
	{
		using Vec2 = GameLib::Vector2;

		// JSONデータの読み込み。
		std::ifstream ifs("Data/test.json", std::ios::in);
		if (ifs.fail()) {
			std::cerr << "failed to read Data/test.json" << std::endl;
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
			if (o["Name"].get<std::string>() == "Player")
			{
				actor = new EditingPlayer(scene, Vec2(x, y));
			}
			else if (o["Name"].get<std::string>() == "Ground")
			{
				actor = new EditingGround(scene, Vec2(x, y));
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