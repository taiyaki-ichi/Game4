#pragma once
#include"Stage/StageScene.hpp"

namespace Game
{
	namespace StageSelect
	{
		constexpr int StageNum = 3;

		class Scene : public Stage::StageScene
		{
		public:
			Scene(int playerPos = 0);
			virtual ~Scene();

			GameLib::Scene* UpdateStageScene() override;

			void SetMoveFlag(int m) { mMoveFlag = m; }

		private:
			int mMoveFlag;
		};
	}
}