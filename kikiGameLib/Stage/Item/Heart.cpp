#include"Heart.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Item
		{

			Heart::Heart(StageScene* scene, const GameLib::Vector2& pos, int o)
				:TransformItem(scene, pos, o)
			{
				SetScale(0.07f);

				GameLib::TextureComponent* texture = new GameLib::TextureComponent(this, "../Assets/Item/heart.png");

				Body* body = new Body(this, "Heart");
				body->SetWidthAndHeight(600.f, 500.f);
				body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
			}

			Heart::~Heart()
			{

			}

		}
	}
}