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
		//’Êí‚ÌActor‚ªXV’†‚É’Ç‰Á‚³‚ê‚È‚¢‚½‚ß‚Ì‘Ò‚¿‚ÌActor
		std::vector<Actor*> mPendingActors;
		bool mUpdatingActors;

	};


}