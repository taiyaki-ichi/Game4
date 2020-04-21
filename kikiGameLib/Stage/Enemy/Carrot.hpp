#pragma once
#include"Stage/StageStateActor.hpp"

namespace GameLib
{
	class AnimComponent;
}

namespace Game
{
	namespace Stage
	{
		class Body;

		namespace Enemy
		{

			class Carrot : public StageStateActor
			{
			public:
				Carrot(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Carrot();

				static const float ACTIVERNGE;

				GameLib::AnimComponent* GetAnim() const { return mAnim; }
				void BreakBody();
				void GoRight();
				void GoLeft();

			private:
				GameLib::AnimComponent* mAnim;
				Body* mBody;
				Body* mWeakness;
			};

			namespace CarrotState
			{
				class Active :public StageState
				{
				public:
					Active(Carrot* carrot,float vY);
					virtual ~Active();

					static const float MAXSPEED;
					static const float RUNPOER;

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					Carrot* mCarrot;
					GameLib::Vector2 mVelocity;
				};

				class Stay : public StageState
				{
				public:
					Stay(Carrot* carrot);
					virtual ~Stay();

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					Carrot* mCarrot;
					float mVelocityY;
				};
			}

		}
	}
}