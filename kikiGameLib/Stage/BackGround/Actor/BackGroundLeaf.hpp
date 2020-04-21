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
				Leaf(StageScene* scene, const GameLib::Vector2& pos,int updateOrder = 0);
				virtual ~Leaf();

				virtual void UpdateBackGround() override;

			};

			class Leaf2 : public BackGroundActor
			{
			public:
				Leaf2(StageScene* s, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Leaf2();
				virtual void UpdateBackGround() override;
			};

			class Wing : public BackGroundActor
			{
			public:
				Wing(StageScene* s, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Wing();

				virtual void UpdateBackGround() override;
			};

		}
	}
}