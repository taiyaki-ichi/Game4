#include"Ground.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"Stage/StageScene.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		Ground::Ground(StageScene* scene,const GameLib::Vector2& pos, float width, float height, int updateOrder)
			:StageActor(scene,pos,updateOrder)
		{
			mBody = new Body(this, "Ground", width, height);
			mBody->SetColor(GameLib::Color::Black);

			using Vec3 = GameLib::Vector3;
			new RectangleComponent(this, width, height, Vec3(50.f, 50.f, 50.f));

			std::cout << "Ground\nPos :" << pos.x << "," << pos.y << "\nWidth :" << width << "\nHeight :" << height << "\n";

		}

		Ground::~Ground()
		{
		}




	}
}