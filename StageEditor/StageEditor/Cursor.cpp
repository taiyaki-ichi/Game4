#include"Cursor.hpp"
#include"EditingScene.hpp"
#include"lib/include/InputState.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"EditingActor.hpp"

namespace StageEditor
{
	Cursor::Cursor(EditingScene* scene)
		:StageActor(scene)
		,mEnter(false)
	{
		mBody = new Game::Stage::Body(this, "Cursor");
		mBody->SetWidthAndHeight(20.f, 20.f);
		mBody->SetColor(GameLib::Color::Red);

	}
	Cursor::~Cursor()
	{
	}
	void Cursor::Input(const GameLib::InputState& state)
	{
		GameLib::Vector2 pos = state.GetMousePos();
		SetPosition(pos);

		mEnter = false;
		if (state.GetState(GameLib::MouseButton::Right) == GameLib::ButtonState::Pressed)
			mEnter = true;
	}
	void Cursor::Hit(Game::Stage::Body* myBody, Game::Stage::Body* theBody)
	{
		auto actor = dynamic_cast<EditingActor*>(theBody->GetOwner());
		if (actor&&mEnter)
		{
			actor->SetState(GameLib::Actor::State::Dead);
		}
	}
}