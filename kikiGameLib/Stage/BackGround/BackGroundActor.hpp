#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		class BackGroundActor : public StageActor
		{
		public:
			BackGroundActor(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
			virtual ~BackGroundActor();

			virtual void UpdateStageActor() override final;
		};

	}
}