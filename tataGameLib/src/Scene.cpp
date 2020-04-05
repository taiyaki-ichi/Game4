#include"include/Scene.hpp"
#include"include/ActorsManager.hpp"
#include"src/SpritesManager.hpp"
#include "..\include\Scene.hpp"


namespace GameLib
{
	Scene::Scene()
	{
		mActorsManagerPtr = new ActorsManager();
		mSpritesManagerPtr = new SpritesManager();
		
	}

	Scene::~Scene()
	{
		
		if (mActorsManagerPtr)
			delete mActorsManagerPtr;
		if (mSpritesManagerPtr)
			delete mSpritesManagerPtr;
		
	}

	void Scene::Input(const InputState& state)
	{
	}

	Scene* Scene::Update()
	{
		return this;
	}

	void Scene::AddActor(Actor* actor)
	{
		mActorsManagerPtr->Add(actor);
	}

	void Scene::RemoveActor(Actor* actor)
	{
		mActorsManagerPtr->Remove(actor);
	}

	ActorsManager* Scene::GetActorsManagerPtr() const
	{
		return mActorsManagerPtr;
	}
	SpritesManager* Scene::GetSpritesManagerPtr() const
	{
		return mSpritesManagerPtr;
	}

}