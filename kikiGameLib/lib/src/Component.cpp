#include"lib/include/Component.hpp"
#include"lib/include/Actor.hpp"
#include"lib/include/ComponentsManager.hpp"

namespace GameLib
{
	Component::Component(Actor* actor, int updateOrder)
		:mOwner(actor)
		, mUpdateOrder(updateOrder)
	{
		mOwner->GetComponentsManager()->Add(this);
	}

	Component::~Component()
	{
		mOwner->GetComponentsManager()->Remove(this);
	}

	void Component::Input(const InputState& state)
	{
	}

	void Component::Update()
	{
	}
}