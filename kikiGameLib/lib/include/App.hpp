#pragma once
#include<string>
#include<memory>

namespace GameLib
{
	class Scene;

	struct WindowData
	{
		const std::string WindowName;
		const float TopleftX;
		const float TopleftY;
		const float WindowWidth;
		const float WindowHeight;
	};

	class App
	{
	protected:
		App() = default;

	public:

		virtual ~App() = default;
		virtual void Start(Scene* startScene) = 0;

	};

	//インターフェース用
	std::shared_ptr<App> CreateAppPtr(const WindowData& windowData, float fps = 60.f);
}