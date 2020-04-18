#pragma once
#include"lib/include/Scene.hpp"

namespace GameLib
{
	class InputState;
}

namespace Game
{
	namespace Title
	{

		class Scene : public GameLib::Scene
		{
		public:
			Scene();
			virtual ~Scene();

			virtual GameLib::Scene* Update() override;
			virtual void Input(const GameLib::InputState& state) override;

		private:
			bool mGoStageSelectFlag;
		};

	}
}