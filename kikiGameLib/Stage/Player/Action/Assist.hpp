#pragma once
#include"Stage/StageActor.hpp"

namespace GameLib
{
	class InputState;
	class TextComponent;
}

namespace Game
{
	namespace Stage
	{

		class Player;
		class RectangleComponent;

		class ActionAssist : public StageActor
		{
		public:
			ActionAssist(Player* p);
			virtual ~ActionAssist();

			virtual void Input(const GameLib::InputState& state) override;
			virtual void UpdateStageActor() override;

		private:
			Player* mPlayer;
			int mCnt;
			GameLib::TextComponent* mText;
			RectangleComponent* mRect1;
			RectangleComponent* mRect2;

		};

	}
}