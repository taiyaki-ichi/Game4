#include"Trampoline.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"

namespace Game
{
	namespace Stage
	{

		float Trampoline::PLAYERPOWER = 20.f;
		float Trampoline::ENEMYPOWER = 20.f;

		Trampoline::Trampoline(StageScene* scene, const GameLib::Vector2& pos)
			:StageActor(scene,pos)
		{
			SetScale(0.5f);

			new GameLib::TextureComponent(this, "../Assets/Other/trampoline.png");

			auto body = new Game::Stage::Body(this, "Trampoline", 700.f, 100.f);
			body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

		}

		Trampoline::~Trampoline()
		{
		}

	}
}