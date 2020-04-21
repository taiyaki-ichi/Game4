#pragma once
#include"Stage/StageStateActor.hpp"

namespace Game
{
	namespace Stage
	{
		class StageActor;

		namespace Enemy
		{
			constexpr float GRAVITY = 5.f;
			constexpr float GRAVITYPOWER = 0.7f;

			class Fall : public StageState
			{
			public:
				Fall(StageActor* actor);
				virtual ~Fall();

				virtual StageState* Update() override;

			private:
				StageActor* mStageActor;
			};

			class DeathTimerState : public StageState
			{
			public:
				DeathTimerState(StageActor* actor,int limit);
				virtual ~DeathTimerState();

				virtual StageState* Update() override;

			private:
				StageActor* mStageActor;
				int mCnt;
				int mLimit;
			};
		}
	}

}