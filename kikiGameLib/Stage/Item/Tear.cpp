#include"Tear.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Item
		{

			Tear::Tear(StageScene* scene, const GameLib::Vector2& pos)
				:TransformItem(scene,pos)
			{
				SetScale(0.15f);

				new GameLib::TextureComponent(this, "../Assets/Item/tear.png");

				auto body = new Game::Stage::Body(this, "Tear", 400.f, 400.f);
				body->SetAdjust(GameLib::Vector2(0.f, 150.f));
				body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
			}

			Tear::~Tear()
			{
			}

		}
	}
}