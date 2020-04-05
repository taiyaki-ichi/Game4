#include"AppImpl.h"
#include"Windows/Window.hpp"
#include"Windows/Event.hpp"
#include"Windows/Time.hpp"
#include"src/DataImpl.hpp"
#include"include/Draw/SpriteComponent.hpp"
#include"Windows/Graphics.hpp"
#include"Windows/Input.hpp"
#include"include/Scene.hpp"
#include"SpritesManager.hpp"
#include"include/ActorsManager.hpp"
#include"include/Actor.hpp"
#include"include/Component.hpp"
#include"include/ComponentsManager.hpp"

#include<iostream>

namespace GameLib
{

	//AppImpl::Input���Ŏg�p
	void InputToScene(Scene*, const InputState&);
	void InputToActor(Actor*, const InputState&);
	//AppImpl::Update���Ŏg�p
	Scene* UpdateScene(Scene*);
	void UpdateActor(Actor*);
	//AppImpl::Draw���Ŏg�p
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
		mWaitTime = 1000.f / fps;

		mGraphicsManagerPtr = new GraphicsManager();
		mInputState = new InputStateImpl();
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

		//�҂��̃A�N�^�[��ǉ�
		for (auto& p : actorsManager->GetPendingActors())
		{
			actors.emplace_back(p);
		}

		//���񂾃A�N�^�[���ړ�
		std::vector<Actor*> deadActors;
		for (auto actor : actors) {
			if (actor->GetState() == Actor::State::Dead) {
				deadActors.emplace_back(actor);
			}
		}
		//���񂾃A�N�^�[�̍폜
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