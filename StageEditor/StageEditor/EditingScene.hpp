#pragma once
#include"Stage/StageScene.hpp"
#include"lib/include/Math.hpp"
#include<string>

namespace GameLib
{
	class TextComponent;
	class InputState;
	class Scene;
	class Vector2;
}

namespace StageEditor
{
	class Cursor;
	class EditingActor;
	class CommandActor;
	class Scale;

	class EditingScene : public Game::Stage::StageScene
	{
	public:
		EditingScene();
		virtual ~EditingScene();

		virtual void Input(const GameLib::InputState& state) override;
		virtual GameLib::Scene* UpdateStageScene() override;

		void AddEditingActor(EditingActor* actor);
		void RemoveEditingActor(EditingActor* actor);

		void Reset();
		void SwitchDrawFlag();

		void LoadStageData(const std::string& fileName);

		const GameLib::Vector2& GetCursorPos() const;

	private:
		void ResetEditingActors();
		void ResetScreemMoveSum();

		std::vector<EditingActor*> mEditingActors;

		Cursor* mCursor;
		CommandActor* mCommandActor;

		GameLib::Vector2 mScreemMoveSum;

		bool mDrawFlag;

		std::vector<Scale*> mScales;
	};

	bool CreateJsonData(std::vector<EditingActor*>& actors,const std::string& fileName,const GameLib::Vector2& adjust);

	class CheckScene : public Game::Stage::StageScene
	{
	public:
		CheckScene(bool drawFlag);
		virtual ~CheckScene();

		virtual void Input(const GameLib::InputState& state) override;
		virtual GameLib::Scene* UpdateStageScene() override;

	private:
		bool mBackFlag;

	};

	bool LoadEditingData(EditingScene* scene, const std::string& fileName);
}