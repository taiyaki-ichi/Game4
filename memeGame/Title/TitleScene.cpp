#include"TitleScene.hpp"
#include"lib/include/InputState.hpp"
#include"SaveData/SaveData.hpp"
#include"lib/include/Actor.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"WindowData.hpp"
#include"StageSelect/StageSelectScene.hpp"

namespace Game
{
	namespace Title
	{
		Scene::Scene()
			:GameLib::Scene()
			,mGoStageSelectFlag(false)
		{
			SaveData::Load();

			auto actor = new GameLib::Actor(this);
			actor->SetPosition(GameLib::Vector2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f+200.f));
			auto t = new GameLib::TextComponent(actor, "../Assets/Font/mplus.ttf");
			t->SetText("S : ‚Í‚¶‚ß‚©‚ç");
		
			if (SaveData::GetStageData(0) == 1)
			{
				auto t2 = new GameLib::TextComponent(actor, "../Assets/Font/mplus.ttf");
				t2->SetText("W : ‚Â‚Ã‚«‚©‚ç");
				t2->SetAdjust(GameLib::Vector2(0.f, -100.f));

			}
		
		}
		
		Scene::~Scene()
		{

		}

		GameLib::Scene* Scene::Update()
		{
			if (mGoStageSelectFlag)
				return new StageSelect::Scene();

			return this;
		}

		void Scene::Input(const GameLib::InputState& state)
		{
			if (state.GetState(GameLib::Key::W) == GameLib::ButtonState::Pressed)
				mGoStageSelectFlag = true;

		}

	}
}