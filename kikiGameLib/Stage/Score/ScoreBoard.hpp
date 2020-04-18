#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		class ScoreBoard : public StageActor
		{
		public:
			ScoreBoard(StageScene* scene);
			virtual ~ScoreBoard();

			virtual void UpdateStageActor() override;

		private:
			int mCnt;
		};
	}
}