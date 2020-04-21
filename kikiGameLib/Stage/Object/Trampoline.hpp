#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{

		class Trampoline : public StageActor
		{
		public:
			Trampoline(StageScene* scene, const GameLib::Vector2& pos);
			virtual ~Trampoline();

			static float PLAYERPOWER;
			static float ENEMYPOWER;
		};

	}
}