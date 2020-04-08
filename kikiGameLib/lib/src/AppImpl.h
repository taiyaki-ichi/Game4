#pragma once
#include"lib/include/App.hpp"

namespace GameLib
{
	class Scene;
	struct WindowHandler;
	class SpritesManager;
	class GraphicsManager;
	class InputStateImpl;
	class SoundManager;

	class AppImpl : public App
	{
	public:

		AppImpl(const WindowData& windowData, float fps = 60.f);
		~AppImpl();

		void Start(Scene* startScene) override final;

	private:

		bool Init(const WindowData& windowData,float fps);
		void RunLoop();
		void Shutdown();

		//RunLoop“à
		void Input();
		void Update();
		void Draw();

		bool mIsRunning;

		Scene* mCurrScene;

		unsigned long mPrevTime;
		unsigned long mWaitTime;

		bool mStartFlag;

		GraphicsManager* mGraphicsManagerPtr;

		InputStateImpl* mInputState;

		SoundManager* mSoundManagerPtr;
	};


}