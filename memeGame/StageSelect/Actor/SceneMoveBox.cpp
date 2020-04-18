#include"SceneMoveBox.hpp"
#include"StageSelect/StageSelectScene.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"

namespace Game
{
	namespace StageSelect
	{

		SceneMoveBox::SceneMoveBox(Scene* scene, const std::string& fileName, int stage, const GameLib::Vector2& pos)
			:Stage::StageActor(scene,pos)
			,mStageNum(stage)
			,mStageSelectScene(scene)
		{
			new GameLib::TextureComponent(this, fileName);
			new Game::Stage::Body(this, "", 700.f, 700.f);

			SetScale(0.1f);
			
		}

		SceneMoveBox::~SceneMoveBox()
		{
		}

		void SceneMoveBox::Hit(Stage::Body* myBody, Stage::Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Player")
			{
				mStageSelectScene->SetMoveFlag(mStageNum);
			}
		}

	}
}