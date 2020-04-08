#include"lib/include/ActorsManager.hpp"
#include"lib/include/Actor.hpp"

namespace GameLib
{
	ActorsManager::ActorsManager()
		:mUpdatingActors(false)
	{

	}

	ActorsManager::~ActorsManager()
	{
	
		while (!mActors.empty()) {
			delete mActors.back();
		}
		while (!mPendingActors.empty()) {
			delete mPendingActors.back();
		}
	}

	void ActorsManager::Add(Actor* actor)
	{
		//XV’†‚È‚çmPendingActor‚É‰Á‚¦‚é
		if (mUpdatingActors) {
			mPendingActors.emplace_back(actor);
		}
		else
		{
			int order = actor->GetUpdateOrder();
			auto iter = mActors.begin();
			for (;
				iter != mActors.end();
				iter++)
			{
				if (order < (*iter)->GetUpdateOrder())
					break;
			}
			mActors.insert(iter, actor);
		}
	}

	void ActorsManager::Remove(Actor* actor)
	{
		auto iter = std::find(mActors.begin(), mActors.end(), actor);
		if (iter != mActors.end())
		{
			mActors.erase(iter);
		}
	}

	void ActorsManager::StartUpdate()
	{
		mUpdatingActors = true;
	}
	void ActorsManager::FinishUpdate()
	{
		mUpdatingActors = false;
	}
}