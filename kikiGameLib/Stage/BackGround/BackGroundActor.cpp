#include"BackGroundActor.hpp"
#include"WindowData.hpp"

namespace Game
{
	namespace Stage
	{

		

		BackGroundActor::BackGroundActor(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
			:StageActor(scene,pos,updateOrder)
		{
		}

		BackGroundActor::~BackGroundActor()
		{
		}

		void BackGroundActor::UpdateStageActor()
		{
			auto pos = GetPosition();

			if (pos.x < -WINDOW_WIDTH * 0.5f)
			{
				float d = -WINDOW_WIDTH * 0.5f - pos.x;
				pos.x = WINDOW_WIDTH * 1.5f - d;
				SetPosition(pos);
			}
			else if (WINDOW_WIDTH * 1.5 < pos.x)
			{
				float  d = pos.x - WINDOW_WIDTH * 1.5f;
				pos.x = -WINDOW_WIDTH * 0.5f + d;
				SetPosition(pos);
			}
		}

	}
}