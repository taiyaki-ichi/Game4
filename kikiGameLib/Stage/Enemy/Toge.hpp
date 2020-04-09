#pragma once
#include"Stage/StageActor.hpp"
#include"Stage/StageState.hpp"

namespace GameLib
{
	class AnimComponent;
	class Vector2;
}

namespace Game
{
	namespace Stage
	{
		class Body;

		namespace Enemy
		{

			class Toge : public StageActor
			{
			public:
				Toge(StageScene* scene,const GameLib::Vector2& pos);
				virtual ~Toge();

				virtual void UpdateStageActor() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

				void BreakBody();

			private:
				StageState* mState;
				GameLib::AnimComponent* mAnim;
				Body* mBody;

			};

			class TogeActive : public StageState
			{
			public:
				TogeActive(Toge* toge);
				virtual ~TogeActive();

				virtual StageState* Update() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				Toge* mToge;
				float mTimer;
			};
			
		}
	}
}