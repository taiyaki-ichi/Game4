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

			class Dogu : public StageStateActor
			{
			public:
				Dogu(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Dogu();

				GameLib::AnimComponent* GetAnim() const { return mAnim; }
				Body* GetBody() const { return mBody; }

			private:
				GameLib::AnimComponent* mAnim;
				Body* mBody;
			};


			namespace DoguState
			{
				constexpr float ACTIVERANGE = 200.f;
				constexpr float SPEED = 1.f;

				class Active : public StageState
				{
				public:
					Active(Dogu* dogu);
					virtual ~Active();

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					Dogu* mDogu;
					int mCnt;
				};

				class Curse : public StageState
				{
				public:
					Curse(Dogu* dogu);
					virtual ~Curse();

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody)override;
				private:
					Dogu* mDogu;
					int mCnt;
				};

			}
		}
	}
}
