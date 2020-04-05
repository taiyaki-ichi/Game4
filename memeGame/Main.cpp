#include"WindowData.hpp"
#include"include/App.hpp"
#include"Stage/StageScene.hpp"
#include"include/Math.hpp"
#include"Stage/StageActor.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"include/InputState.hpp"

#include<iostream>

namespace Game
{
	using Vec2 = GameLib::Vector2;

	class MyRect : public Stage::StageActor
	{
	public:
		MyRect(Stage::StageScene* scene)
			:Stage::StageActor(scene)
		{
			mBody = new Stage::Body(this, "", 10.f, 300.f);
			mBody->SetColor(GameLib::Vector3(0, 255, 0));
		}

		void Input(const GameLib::InputState& state) override
		{
			GameLib::Vector2 pos = state.GetMousePos();
			SetPosition(pos);
		}

		void UpdateStageActor() override
		{
			mBody->SetColor(GameLib::Vector3(0, 0, 0));
			float rot = GetRotation();
			rot += 0.01;
			SetRotation(rot);

		}

		void Hit(Stage::Body* myBody, Stage::Body* theBody) override
		{
			std::string name = theBody->GetName();
			if (name == "red")
				myBody->SetColor(GameLib::Color::Red);
			else if (name == "green")
				myBody->SetColor(GameLib::Color::Green);
			else if (name == "blue")
				myBody->SetColor(GameLib::Color::Blue);
		}

	private:
		Stage::Body* mBody;
	};

	class Red : public Stage::StageActor
	{
	public:
		Red(Stage::StageScene* scene, const Vec2& pos)
			:Stage::StageActor(scene, pos)
		{
			auto body = new Stage::Body(this, "red", 300.f, 10.f);
			body->SetColor(GameLib::Color::Red);
		}
	};
	class Green : public Stage::StageActor
	{
	public:
		Green(Stage::StageScene* scene, const Vec2& pos)
			:Stage::StageActor(scene, pos)
		{
			auto body = new Stage::Body(this, "green", 50.f, 50.f);
			body->SetColor(GameLib::Color::Green);
		}
	};
	class Blue : public Stage::StageActor
	{
	public:
		Blue(Stage::StageScene* scene, const Vec2& pos)
			:Stage::StageActor(scene, pos)
		{
			auto body = new Stage::Body(this, "blue", 100.f, 100.f);
			body->SetColor(GameLib::Color::Blue);
		}
	};

	class MyScene : public Stage::StageScene
	{
	public:
		MyScene()
			:Stage::StageScene()
		{

			new MyRect(this);
			new Red(this, Vec2(300.f, 250.f));
			new Green(this, Vec2(700.f, 300.f));
			new Blue(this, Vec2(500.f, 500.f));

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
