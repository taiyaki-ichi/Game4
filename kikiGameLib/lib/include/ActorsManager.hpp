#pragma once
#include<vector>

namespace GameLib
{
	class Actor;

	class ActorsManager
	{
	public:
		ActorsManager();
		~ActorsManager();

		void Add(Actor* actor);
		void Remove(Actor* actor);

		void StartUpdate();
		void FinishUpdate();

		std::vector<Actor*>& GetActors() { return mActors; }
		std::vector<Actor*>& GetPendingActors() { return mPendingActors; }

	private:
		std::vector<Actor*> mActors;
		//通常のActorが更新中に追加されないための待ちのActor
		std::vector<Actor*> mPendingActors;
		bool mUpdatingActors;

	};


}