#pragma once
#include"Stage/StageActor.hpp"
#include<string>

namespace Game
{
	namespace StageSelect
	{
		class Scene;

		class StageIsland : public Game::Stage::StageActor
		{
		public:
			StageIsland(Scene* scene, int stageNum, const std::string& boxFileName);
			virtual ~StageIsland();

			static float WIDTH;
		};


	}

}