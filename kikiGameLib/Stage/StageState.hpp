#pragma once

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
			virtual void Hit(Body* myBody, Body* theBody) {};
		};

	}
}