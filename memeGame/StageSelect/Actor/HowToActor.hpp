#pragma once
#include"Stage/StageActor.hpp"

namespace GameLib
{
	class AnimComponent;
}

namespace Game
{
	namespace StageSelect
	{
		class Scene;

		namespace HowTo
		{

			class Left : public Stage::StageActor
			{
			public:
				Left(Scene* scene,const GameLib::Vector2& pos);
				virtual ~Left();

			};

			class Right : public Stage::StageActor
			{
			public:
				Right(Scene* scene, const GameLib::Vector2& pos);
				virtual ~Right();

			};

			class Jump : public Stage::StageActor
			{
			public:
				Jump(Scene* scene, const GameLib::Vector2& pos);
				virtual ~Jump();

				virtual void UpdateStageActor() override;

			private:
				GameLib::AnimComponent* mAnim;
				float mVelocityY;
				int mCnt;
			};
		}


	}
}