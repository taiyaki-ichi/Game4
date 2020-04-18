#pragma once
#include"Stage/StageScene.hpp"

namespace Game
{
	namespace StageSelect
	{
		class Scene : public Stage::StageScene
		{
		public:
			Scene();
			virtual ~Scene();

			GameLib::Scene* UpdateStageScene() override;

			void SetMoveFlag(int m) { mMoveFlag = m; }

		private:
			int mMoveFlag;
		};
	}
}