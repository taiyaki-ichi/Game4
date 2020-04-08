#include"Stage/StageScene.hpp"
#include"lib/include/InputState.hpp"
#include"lib/include/App.hpp"
#include"WindowData.hpp"

#include<iostream>
#include<string>

namespace Game
{
	class MyScene : public Stage::StageScene
	{
	public:
		MyScene()
			:Stage::StageScene()
		{


			//Game::Stage::LoadStageData(this, "Stage/Data/aaa.json");
			
		}
		virtual ~MyScene() {};

		virtual void Input(const GameLib::InputState& state) override
		{
			if (state.GetState(GameLib::MouseButton::Left) == GameLib::ButtonState::Pressed)
				std::cout << "L";
			if (state.GetState(GameLib::MouseButton::Middle) == GameLib::ButtonState::Pressed)
				std::cout << "M";
			if (state.GetState(GameLib::MouseButton::Right) == GameLib::ButtonState::Pressed)
				std::cout << "R";
		}

	};

}

#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__) 
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);

	auto app = GameLib::CreateAppPtr({ "",400,100,Game::WINDOW_WIDTH,Game::WINDOW_HEIGHT });
	app->Start(new Game::MyScene());
	return 0;
}
