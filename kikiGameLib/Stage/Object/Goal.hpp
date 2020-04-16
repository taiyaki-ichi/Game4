#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		class Goal;

		namespace GoalParts
		{
			class Rect : public StageActor
			{
			public:
				Rect(StageScene* scene,Goal* goal, const GameLib::Vector2& pos);
				virtual ~Rect();

				virtual void UpdateStageActor() override;

			private:
				Goal* mGoal;
			};

			class Kira : public StageActor
			{
			public:

				static const int DEATHTIME;
				static const float MAXSCALE;

				Kira(StageScene* scene, const GameLib::Vector2& pos);
				virtual ~Kira();

				virtual void UpdateStageActor() override;

			private:
				int mCnt;
			};
		}

		class Goal : public StageActor
		{
		public:
			Goal(StageScene* scene, const GameLib::Vector2& pos);
			virtual ~Goal();

			virtual void UpdateStageActor();
			virtual void Hit(Body* myBody, Body* theBody) override;


		};

	}
}