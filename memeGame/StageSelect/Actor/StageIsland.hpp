#pragma once
#include"Stage/StageActor.hpp"
#include<string>

namespace Game
{
	namespace StageSelect
	{
		class Scene;
		class BackGroundManager;
		class BackGround;

		class StageIsland : public Game::Stage::StageActor
		{
		public:
			StageIsland(Scene* scene, int stageNum, const std::string& boxFileName);
			virtual ~StageIsland();

			static float WIDTH;

			virtual void UpdateStageActor() override;

			void AddBackGround(BackGround* b);

		private:
			BackGroundManager* mBackGroundManager;

			bool mBackGroundActiveFlag;
		};

		void CreateBackGround(StageIsland* s, int stageNum);

	}

}