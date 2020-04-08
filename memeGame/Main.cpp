#include"WindowData.hpp"
#include"include/App.hpp"
#include"Stage/StageScene.hpp"
#include"include/Math.hpp"
#include"Stage/StageActor.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"include/InputState.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/Object/Ground.hpp"
#include"Stage/Player.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"include/Draw/AnimComponent.hpp"
#include"include/Data.hpp"
#include"include/Draw/TextComponent.hpp"
#include"include/InputState.hpp"
#include"include/SoundComponent.hpp"
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
			using Vec2 = GameLib::Vector2;
			new Stage::Ground(this, Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 50.f), WINDOW_WIDTH, 100.f);
			auto player = new Stage::Player(this, Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));

			auto s = new GameLib::SoundComponent(player, "Assets/Sound/sound001.wav");
			s->Play(true);
			
		}
		virtual ~MyScene() {};

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
