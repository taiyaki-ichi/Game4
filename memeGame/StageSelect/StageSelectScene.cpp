#include"StageSelectScene.hpp"
#include"SaveData/SaveData.hpp"
#include"Actor/StartIsland.hpp"
#include"Stage/Player/Player.hpp"
#include"Actor/StageIsland.hpp"

namespace Game
{
	namespace StageSelect
	{
		Scene::Scene()
			:Stage::StageScene()
			,mMoveFlag(0)
		{
			SaveData::SetStageData(0, 1);
			new Stage::Player(this, GameLib::Vector2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 350.f));

			new StartIsland(this);

			new StageIsland(this, 1, "../Assets/Box/001.png");
		}

		Scene::~Scene()
		{

		}

		GameLib::Scene* Scene::UpdateStageScene()
		{
			

			return this;
		}

	}
}