#pragma once
#include"Stage/StageActor.hpp"

namespace GameLib
{
	class TextComponent;
}

namespace StageEditor
{
	class EditingScene;

	class Scale : public Game::Stage::StageActor
	{
	public:
		Scale(EditingScene* scene, bool isX, float num);
		virtual ~Scale();

		virtual void UpdateStageActor() override;

		virtual void AdjustPosSub(const GameLib::Vector2& vec) override;

		void Reset();

	private:
		float mNum;
		bool mIsX;
		GameLib::TextComponent* mText;

		float mStartNum;
	};
}