#pragma once
#include"TransformItem.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Item
		{
			class Heart : public TransformItem
			{
			public:
				Heart(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Heart();
			};

		}
	}
}