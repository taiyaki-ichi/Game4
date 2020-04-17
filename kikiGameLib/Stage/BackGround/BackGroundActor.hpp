#pragma once
#include"Stage/StageActor.hpp"
#include<string>


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
			virtual void UpdateBackGround() {}
		};

		void CreateBackGrounds(StageScene* scene, const std::string& fileName, int num,float posY, float relativeRate,
			float drawOrder, float scele = 0.5f);

		void CreateForestBackGround(StageScene* scene);
	}
}