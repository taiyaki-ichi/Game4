#pragma once
#include"Stage/StageScene.hpp"

namespace Game
{
	namespace Stage
	{
		class GameStageScene : public StageScene
		{
		public:
			GameStageScene(int stageNum,const std::string& fileName);
			virtual ~GameStageScene();

			GameLib::Scene* UpdateStageScene() override;

		private:
			int mStageNum;
		};

	}
}