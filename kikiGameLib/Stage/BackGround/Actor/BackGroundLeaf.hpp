#pragma once
#include"Stage/BackGround/BackGroundActor.hpp"

namespace Game
{
	namespace Stage
	{
		namespace BackGround
		{
			class Leaf : public BackGroundActor
			{
			public:
				Leaf(StageScene* scene, const GameLib::Vector2& pos,bool is200 ,int updateOrder = 0);
				virtual ~Leaf();

				virtual void UpdateBackGround() override;

			};

	
		}
	}
}