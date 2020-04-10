#pragma once
#include"StageActor.hpp"

namespace GameLib
{
	class InputState;
}

namespace Game
{
	namespace Stage
	{
		class Body; 

		class StageState 
		{
		public:
			StageState() {};
			virtual ~StageState() {};

			virtual void Input(const GameLib::InputState&) {}
			virtual StageState* Update() { return this; }
			virtual void Hit(Body* myBody, Body* theBody) {}

			virtual void AdjustPosSub(const GameLib::Vector2& vec) {}
		};

		class StageStateActor : public StageActor
		{
		public:
			StageStateActor(StageScene* scene,const GameLib::Vector2& pos ,int updateOrder = 0);
			virtual ~StageStateActor();

			virtual void Input(const GameLib::InputState& state) override final;
			virtual void UpdateStageActor() override final;
			virtual void Hit(Body* myBody, Body* theBody) override final;

			virtual void AdjustPosSub(const GameLib::Vector2& vec) override final;

			void SetStageState(StageState* state);

		private:
			StageState* mState;
		};

	}
}