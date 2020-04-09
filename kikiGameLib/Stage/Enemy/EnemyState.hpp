#pragma once
#include"Stage/StageState.hpp"

namespace Game
{
	namespace Stage
	{
		class StageActor;

		namespace Enemy
		{
			constexpr float GRAVITY = 5.f;

			class Fall : public StageState
			{
			public:
				Fall(StageActor* actor);
				virtual ~Fall();

				virtual StageState* Update() override;

			private:
				StageActor* mStageActor;
			};
		}
	}

}