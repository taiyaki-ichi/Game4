#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		class Body;
	}
}

namespace GameLib
{
	class InputState;
}

namespace StageEditor
{
	class EditingScene;

	class Cursor : public Game::Stage::StageActor
	{
	public:
		Cursor(EditingScene* scene);
		virtual ~Cursor();

		virtual void Input(const GameLib::InputState& state) override;
		virtual void Hit(Game::Stage::Body* myBody, Game::Stage::Body* theBody) override;

	private:
		Game::Stage::Body* mBody;
		bool mEnter;
	};

}