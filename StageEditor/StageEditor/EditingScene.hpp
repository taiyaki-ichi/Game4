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

	class EditingScene : public Game::Stage::StageScene
	{
	public:
		EditingScene();
		virtual ~EditingScene();

		virtual void Input(const GameLib::InputState& state) override;
		virtual GameLib::Scene* UpdateStageScene() override;

		bool AddEditingActor(EditingActor* actor);
		void RemoveEditingActor(EditingActor* actor);

		void SetCurrEditingActor(EditingActor* actor) { mCurrEditingActor = actor; }

	private:
		GameLib::TextComponent* mText;
		Cursor* mCursor;

		EditingActor* mCurrEditingActor;

		std::vector<EditingActor*> mEditingActors;

		bool mGoFlag;
	};

	std::string GetKey(const GameLib::InputState& state);

	bool CreateJsonData(std::vector<EditingActor*>& actors,const std::string& fileName);

	class CheckScene : public Game::Stage::StageScene
	{
	public:
		CheckScene();
		virtual ~CheckScene();


	};
}