#pragma once
#include"Stage/StageActor.hpp"
#include"Stage/StageState.hpp"

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
			class Frog : public StageActor
			{
			public:
				Frog(StageScene* scene,const GameLib::Vector2& pos,float h);
				virtual ~Frog();

				virtual void UpdateStageActor() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

				void BreakBody();
				GameLib::AnimComponent* GetAnim() const { return mAnim; }

			private:
				GameLib::AnimComponent* mAnim;
				Body* mBody;
				Body* mWeakness;
				StageState* mState;
			};

			class FrogActive : public StageState
			{
			public:
				FrogActive(Frog* frog,float jumpPower);
				virtual ~FrogActive();

				virtual StageState* Update() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				float mVelocityY;
				bool mOnGround;
				Frog* mFrog;
				int mCnt;
				float mJumpPower;
				bool mFlatFlag;
			};

		}
	}
}