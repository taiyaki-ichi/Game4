#pragma once
#include"Stage/StageScene.hpp"
#include<string>

namespace GameLib
{
	class TextComponent;
	class InputState;
	class Scene;
}

namespace StageEditor
{
	class Cursor;
	class EditingActor;
	class CommandActor;

	class EditingScene : public Game::Stage::StageScene
	{
	public:
		EditingScene();
		virtual ~EditingScene();

		virtual GameLib::Scene* UpdateStageScene() override;

		void AddEditingActor(EditingActor* actor);
		void RemoveEditingActor(EditingActor* actor);
		void ResetEditingActors();

	private:
		std::vector<EditingActor*> mEditingActors;

		Cursor* mCursor;
		CommandActor* mCommandActor;
	};

	bool CreateJsonData(std::vector<EditingActor*>& actors,const std::string& fileName);

	class CheckScene : public Game::Stage::StageScene
	{
	public:
		CheckScene();
		virtual ~CheckScene();

		virtual void Input(const GameLib::InputState& state) override;
		virtual GameLib::Scene* UpdateStageScene() override;

	private:
		bool mBackFlag;

	};

	bool LoadEditingData(EditingScene* scene);
}