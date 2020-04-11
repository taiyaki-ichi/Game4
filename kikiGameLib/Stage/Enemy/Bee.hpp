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
		class StageState;
		class Body;

		namespace Enemy
		{

			class Bee : public StageStateActor
			{
			public:
				//pattern 0:直線　1:時計回り　2:反時計回り
				Bee(StageScene* scene, int pattern, const GameLib::Vector2& p1, const GameLib::Vector2& p2);
				virtual ~Bee();

			private:

				GameLib::AnimComponent* mAnim;
				Body* mBody;
			};

			class StraightBeeActive : public StageState
			{
			public:
				StraightBeeActive(Bee* bee, const GameLib::Vector2& p1, const GameLib::Vector2& p2);
				virtual ~StraightBeeActive();

				virtual StageState* Update() override;
				virtual void Hit(Body* myBody, Body* theBody) override;
				virtual void AdjustPosSub(const GameLib::Vector2& vec) override;

			private:
				Bee* mBee;

				GameLib::Vector2 mPoint1;
				GameLib::Vector2 mMoveVec;

				int mCnt;
			};

			class CircleBeeActive : public StageState
			{
			public:
				CircleBeeActive(Bee* bee, const GameLib::Vector2& p1, const GameLib::Vector2& p2,int paterrn);
				virtual ~CircleBeeActive();

				virtual StageState* Update() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

				virtual void AdjustPosSub(const GameLib::Vector2& vec) override;

			private:
				Bee* mBee;

				GameLib::Vector2 mCenter;
				GameLib::Vector2 mRediusVec;

				float mRot;
				bool mIsClockwise;

			};

			void ActiveBeeHit(Body* myBody, Body* theBody);

		}
	}
}