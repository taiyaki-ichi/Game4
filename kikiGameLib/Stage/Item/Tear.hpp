#pragma once
#include"TransformItem.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Item
		{
			class Tear : public TransformItem
			{
			public:
				Tear(StageScene* scene, const GameLib::Vector2& pos);
				virtual ~Tear();


			};

		}
	}
}