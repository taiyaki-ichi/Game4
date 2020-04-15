#include"AppImpl.h"
#include"Windows/Window.hpp"
#include"Windows/Event.hpp"
#include"Windows/Time.hpp"
#include"lib/src/DataImpl.hpp"
#include"lib/include/Draw/SpriteComponent.hpp"
#include"Windows/Graphics.hpp"
#include"Windows/Input.hpp"
#include"lib/include/Scene.hpp"
#include"SpritesManager.hpp"
#include"lib/include/ActorsManager.hpp"
#include"lib/include/Actor.hpp"
#include"lib/include/Component.hpp"
#include"lib/include/ComponentsManager.hpp"
#include"lib/src/Windows/Sound.hpp"

#include<iostream>

namespace GameLib
{

	//AppImpl::Input内で使用
	void InputToScene(Scene*, const InputState&);
	void InputToActor(Actor*, const InputState&);
	//AppImpl::Update内で使用
	Scene* UpdateScene(Scene*);
	void UpdateActor(Actor*);
	//AppImpl::Draw内で使用
	void DrawScene(Scene*);

	AppImpl::AppImpl(const WindowData& windowData, float fps )
		:App()
		, mIsRunning(true)
		,mPrevTime(0)
		, mWaitTime(0)
		, mCurrScene(nullptr)
		,mStartFlag(true)
	{
		mStartFlag = Init(windowData, fps);
		mWaitTime = static_cast<unsigned long>(1000.f / fps);

		mGraphicsManagerPtr = new GraphicsManager();
		mInputState = new InputStateImpl();
		mSoundManagerPtr = new SoundManager();
	}

	AppImpl::~AppImpl()
	{
	}

	void AppImpl::Start(Scene* startScene)
	{
		mCurrScene = startScene;

		if (mStartFlag && mCurrScene)
		{
			mPrevTime = GetTime();
			RunLoop();
		}
		Shutdown();
	}

	bool AppImpl::Init(const WindowData& windowData,float fps)
	{
	
		DataImpl::SetFPS(fps);

		if (!CreateAppWindow(windowData))
			return false;

		if (!mGraphicsManagerPtr->Init())
			return false;

		if (!mSoundManagerPtr->Init())
			return false;

		if (!mInputState->Init())
			return false;

		return true;

	}

	void AppImpl::RunLoop()
	{
		while (mIsRunning)
		{
			Input();
			Update();
			Draw();
		}
	}

	void AppImpl::Shutdown()
	{
		if (mCurrScene)
			delete mCurrScene;
		if (mGraphicsManagerPtr)
			delete mGraphicsManagerPtr;
		if (mSoundManagerPtr)
			delete mSoundManagerPtr;
		if (mInputState)
			delete mInputState;
		DataImpl::Unload();
	}

	void AppImpl::Input()
	{
		mIsRunning = PollEvent();
		mInputState->Update();

		if (mCurrScene)
			InputToScene(mCurrScene, *mInputState);

	}

	void AppImpl::Update()
	{
		Wait(mPrevTime, mWaitTime);
		mPrevTime = GetTime();

		if (mCurrScene)
		{
			Scene* next = UpdateScene(mCurrScene);
			if (next != mCurrScene)
			{
				delete mCurrScene;
				mCurrScene = next;
			}
		}

	}

	void AppImpl::Draw()
	{
		DrawStart();
		if (mCurrScene)
			DrawScene(mCurrScene);
		DrawEnd();
	}

	std::shared_ptr<App> CreateAppPtr(const WindowData& windowData, float fps)
	{
		return std::make_shared<AppImpl>(windowData, fps);
	}

	
	void InputToScene(Scene* scene,const InputState& state)
	{
		auto actors = scene->GetActorsManagerPtr();
		actors->StartUpdate();
		for (auto& a : actors->GetActors())
		{
			InputToActor(a, state);
		}

		scene->Input(state);
	}

	void InputToActor(Actor* actor, const InputState& state)
	{
		if (actor->GetState() == Actor::State::Active)
		{
			for (auto& comp : actor->GetComponentsManager()->GetComponents())
			{
				comp->Input(state);
			}
			actor->Input(state);
		}
	}

	Scene* UpdateScene(Scene* scene)
	{
		auto actorsManager = scene->GetActorsManagerPtr();

		actorsManager->StartUpdate();
		auto& actors = actorsManager->GetActors();
		for (auto& a : actors)
		{
			UpdateActor(a);
		}
		actorsManager->FinishUpdate();

		//待ちのアクターを追加
		for (auto& p : actorsManager->GetPendingActors())
		{
			actors.emplace_back(p);
		}
		actorsManager->GetPendingActors().clear();

		//死んだアクターを移動
		std::vector<Actor*> deadActors;
		for (auto actor : actors) {
			if (actor->GetState() == Actor::State::Dead) {
				deadActors.emplace_back(actor);
			}
		}
		//死んだアクターの削除
		for (auto actor : deadActors) {
			delete actor;
		}

		return scene->Update();
	}

	void UpdateActor(Actor* actor)
	{
		if (actor->GetState() == Actor::State::Active)
		{
			actor->Update();
			for (auto& comp : actor->GetComponentsManager()->GetComponents())
			{
				comp->Update();
			}
		}
	}

	void DrawScene(Scene* scene)
	{
		for (auto& sprite : scene->GetSpritesManagerPtr()->GetSprites())
			sprite->Draw();
	}

}