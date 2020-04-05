#pragma once
#include"include/Component.hpp"

namespace Game
{
	namespace Stage
	{
		class StageActor;

		class StageComponent : public GameLib::Component
		{
		public:
			StageComponent(StageActor* actor, int updateOrder = 0);
			virtual ~StageComponent();

			StageActor* GetStageOwner() const { return mStageOwner; }

		private:
			StageActor* mStageOwner;
		};
	}
}