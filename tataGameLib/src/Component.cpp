#include"include/Component.hpp"
#include"include/Actor.hpp"
#include"include/ComponentsManager.hpp"

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