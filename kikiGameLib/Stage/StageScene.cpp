#include"StageScene.hpp"
#include"Stage/CollisionDetection/Manager.hpp"
#include"lib/include/Math.hpp"
#include"Player.hpp"
#include"Object/Ground.hpp"
#include <fstream>
#include"picojson/picojson.hpp"
#include"Enemy/Triple.hpp"
#include"Enemy/Toge.hpp"
#include"Enemy/Frog.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{

		StageScene::StageScene()
			:GameLib::Scene()
			,mStageLeft(0.f)
			,mStageRight(FLT_MAX)
			,mPlayer(nullptr)
		{
			mTree = new Liner4Tree(TREELEVEL,
				CollisionDetectionScope::Left, CollisionDetectionScope::Top, CollisionDetectionScope::Right, CollisionDetectionScope::Bottom);
	
			if (!mTree)
				std::cout << "nullptr\n";

		}

		StageScene::~StageScene()
		{
			if (mTree)
				delete mTree;
		}

		GameLib::Scene* StageScene::Update()
		{
			auto next = UpdateStageScene();
			if (mTree)
				mTree->SearchCellArray();

			AdjustScreen();

			return next;
		}

		GameLib::Scene* StageScene::UpdateStageScene()
		{
			return this;
		}

		void StageScene::AddStageActor(StageActor* actor)
		{
			mStageActors.emplace_back(actor);
		}

		void StageScene::RemoveStageActor(StageActor* actor)
		{
			auto iter = std::find(mStageActors.begin(), mStageActors.end(), actor);
			if (iter != mStageActors.end())
			{
				mStageActors.erase(iter);
			}
		}

		void StageScene::AdjustScreen()
		{
			
			using Vec2 = GameLib::Vector2;
			if (mPlayer)
			{
				Vec2 playerPos = mPlayer->GetPosition();

				if (mStageRight - mStageLeft > WINDOW_WIDTH)
				{
					Vec2 adjust = Vec2(0.f, 0.f);
					
					float d;

					float top = 150.f;
					float buttom = WINDOW_HEIGHT - 150.f;

					d = top - playerPos.y;
					if (d > 0)
					{
						playerPos.y = top;
						adjust.y = -d;
					}

					d = playerPos.y - buttom;
					if (d > 0)
					{
						playerPos.y = buttom;
						adjust.y = d;
					}

					//さらにスクリーンが端にない時
					if (playerPos.x - mStageLeft > WINDOW_WIDTH / 2.f && mStageRight - playerPos.x > WINDOW_WIDTH / 2.f)
					{
						adjust.x = playerPos.x - Game::WINDOW_WIDTH / 2.f;
						playerPos.x = Game::WINDOW_WIDTH / 2.f;
					}

					MoveScreen(adjust);
					mPlayer->SetPosition(playerPos);
				}
			}
			
		}

		void StageScene::MoveScreen(const GameLib::Vector2& vec)
		{
			for (auto& actor : mStageActors)
			{
				actor->AdjustPos(-1.f * vec);
			}

			mStageLeft -= vec.x;
			mStageRight -= vec.x;

		}

		bool LoadStageData(StageScene* scene, const std::string& fileName)
		{
			using Vec2 = GameLib::Vector2;

			// JSONデータの読み込み。
			std::ifstream ifs(fileName, std::ios::in);
			if (ifs.fail()) {
				std::cerr << "failed to read " << fileName << std::endl;
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
			for (const auto& e : ary)
			{
				picojson::object o = e.get<picojson::object>();
	

				///////////////////////////////////////////////////////////////////////////////////////////////////////////
				//ここに追加
				//////////////////////////////////////////////////////////////////////////////////////////////////////////

				if (o["Name"].get<std::string>() == "Player")
				{
					Vec2 pos = Vec2(o["Data1"].get<double>(), o["Data2"].get<double>());
					new Player(scene, pos);
				}
				else if (o["Name"].get<std::string>() == "Ground")
				{
					Vec2 point1 = Vec2(o["Data1"].get<double>(), o["Data2"].get<double>());
					Vec2 point2 = Vec2(o["Data3"].get<double>(), o["Data4"].get<double>());
					
					float x = point1.x - point2.x;
					float y = point1.y - point2.y;

					float xx = (x > 0) ? point2.x : point1.x;
					float yy = (y > 0) ? point2.y : point1.y;

					float w = GameLib::Math::Abs(x);
					float h = GameLib::Math::Abs(y);

					Vec2 pos = Vec2(xx + w / 2.f, yy + h / 2.f);

					new Ground(scene, pos, w, h);
				}
				else if (o["Name"].get<std::string>() == "Triple")
				{
					Vec2 pos = Vec2(o["Data1"].get<double>(), o["Data2"].get<double>());
					new Enemy::Triple(scene, pos);
				}
				else if (o["Name"].get<std::string>() == "Toge")
				{
					Vec2 pos = Vec2(o["Data1"].get<double>(), o["Data2"].get<double>());
					new Enemy::Toge(scene, pos);
				}
				else if (o["Name"].get<std::string>() == "Frog")
				{
					Vec2 pos = Vec2(o["Data1"].get<double>(), o["Data2"].get<double>());
					float h = o["Data2"].get<double>() - o["Data4"].get<double>();
					new Enemy::Frog(scene, pos, h);

				}


			}

			return true;

		}

}

		
}