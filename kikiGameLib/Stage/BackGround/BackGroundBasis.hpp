#pragma once
#include"Stage/StageStateActor.hpp"

namespace Game
{
	namespace Stage
	{
		
		class BackGroundBasis : public StageActor
		{
		public:
			BackGroundBasis(StageScene* scene,int updateOrder = 0);
			virtual ~BackGroundBasis();

			virtual void AdjustPosSub(const GameLib::Vector2& vec);

		private:
			GameLib::Vector2 mMoveSum;

		};
		class Horaizon180 : public StageActor
		{
		public:
			Horaizon180(StageScene* scene, int updateOrder = 0);
			virtual ~Horaizon180();
			virtual void AdjustPosSub(const GameLib::Vector2& vec);
		};
		class Horaizon230 : public StageActor
		{
		public:
			Horaizon230(StageScene* scene, int updateOrder = 0);
			virtual ~Horaizon230();
			virtual void AdjustPosSub(const GameLib::Vector2& vec);
		};

	}
}