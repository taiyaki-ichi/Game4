#include"StartIsland.hpp"
#include"Stage/Object/Ground.hpp"
#include"StageSelect/StageSelectScene.hpp"

namespace Game
{
	namespace StageSelect
	{
		float StartIsland::WIDTH = 800.f;

		StartIsland::StartIsland(Scene* scene)
			:Stage::StageActor(scene)
		{
			SetPosition(GameLib::Vector2(WIDTH / 2.f, WINDOW_HEIGHT / 2.f));

			new Stage::Ground(scene, GameLib::Vector2(WIDTH / 2.f, WINDOW_HEIGHT - 75.f), WIDTH, 150.f);
			new Stage::Ground(scene, GameLib::Vector2(-50.f, WINDOW_HEIGHT / 2.f), 100.f, WINDOW_HEIGHT);
		}

		StartIsland::~StartIsland()
		{
		}

	}
}
