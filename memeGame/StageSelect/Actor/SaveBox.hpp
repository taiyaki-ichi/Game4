#pragma once
#include"Stage/StageActor.hpp"

namespace GameLib
{
	class TextComponent;
}

namespace Game
{
	namespace StageSelect
	{
		class Scene;

		class SaveBox : public Stage::StageActor
		{
		public:
			SaveBox(Scene* s, const GameLib::Vector2& pos);
			virtual ~SaveBox();

			virtual void UpdateStageActor() override;
			virtual void Hit(Stage::Body* myBody, Stage::Body* theBody) override;

		private:
			int mCnt;
			GameLib::TextComponent* mText;
		};
	}
}