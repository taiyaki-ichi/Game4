#pragma once
#include"Stage/StageActor.hpp"
#include<string>

namespace Game
{
	namespace StageSelect
	{
		class Scene;

		class SceneMoveBox : public Stage::StageActor
		{
		public:
			SceneMoveBox(Scene* scene, const std::string& fileName, int stage, const GameLib::Vector2& pos);
			virtual ~SceneMoveBox();

			virtual void Hit(Stage::Body* myBody, Stage::Body* theBody) override;

		private:
			Scene* mStageSelectScene;
			int mStageNum;
		};
	}
}