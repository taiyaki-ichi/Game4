#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace StageSelect
	{
		class Scene;

		class StartIsland : public Stage::StageActor
		{
		public:
			StartIsland(Scene* scene);
			virtual ~StartIsland();
		};
	}
}