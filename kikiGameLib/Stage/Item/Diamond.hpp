#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		class Body;

		namespace Item
		{

			class Diamond : public StageActor
			{
			public:
				Diamond(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Diamond();

				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				Body* mBody;

			};

		}

	}
}