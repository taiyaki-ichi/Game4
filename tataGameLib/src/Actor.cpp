#include"include/Actor.hpp"
#include"include/ComponentsManager.hpp"
#include"include/Scene.hpp"
#include"include/ActorsManager.hpp"

namespace GameLib
{
	Actor::Actor(Scene* scene, int updateOrder)
		:mScene(scene)
		, mState(State::Active)
		, mUpdateOrder(updateOrder)
		, mPosition(Vector2())
		, mRotation(0.f)
		, mScale(1.f)
	{
		mComponentsManager = new ComponentsManager();
		scene->GetActorsManagerPtr()->Add(this);
	}

	Actor::~Actor()
	{
		if (mComponentsManager)
			delete mComponentsManager;
		GetScene()->GetActorsManagerPtr()->Remove(this);
	}

	void Actor::Input(const InputState& state)
	{

	}

	void Actor::Update()
	{

	}
}