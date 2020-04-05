#include"StageComponent.hpp"
#include"StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		StageComponent::StageComponent(StageActor* actor, int updateOrder)
			:GameLib::Component(actor,updateOrder)
			,mStageOwner(actor)
		{
		}
		StageComponent::~StageComponent()
		{
		}
	}

}