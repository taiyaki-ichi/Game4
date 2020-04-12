#pragma once
#include"Stage/StageActor.hpp"


namespace GameLib
{
	class LineComponent;
	class InputState;
}


namespace Game
{
	namespace Stage
	{
		class RectangleComponent;
		class Body;

		namespace PlayerAction
		{

			class Beam : public StageActor
			{
			public:
				Beam(StageScene* scene, const GameLib::Vector2& playerPos,bool isRight, int updateOrder = 0);
				virtual ~Beam();

				virtual void UpdateStageActor() override;

				static int GetNum() { return mBeamNum; }

			private:
				int mCnt;
				bool mIsRight;
				static int mBeamNum;

			};

			namespace BeamEffect
			{

				class LineCharge : public StageActor
				{
				public:
					LineCharge(StageScene* scene, const GameLib::Vector2& pos, const GameLib::Vector2& center, int updateOrder = 0);
					virtual ~LineCharge();

					virtual void UpdateStageActor() override;
					virtual void AdjustPosSub(const GameLib::Vector2& vec) override;

				private:
					GameLib::LineComponent* mLine;
					GameLib::Vector2 mLinePos;
				};

				class RectCharge : public StageActor
				{
				public:
					RectCharge(StageScene* scene, const GameLib::Vector2& pos, const GameLib::Vector2& center, int updateOrder = 0);
					virtual ~RectCharge();

					virtual void UpdateStageActor() override;
					virtual void AdjustPosSub(const GameLib::Vector2& vec) override;
				private:
					RectangleComponent* mRect;
					GameLib::Vector2 mCenter;
				};


				class Charge : public StageActor
				{
				public:
					Charge(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
					virtual ~Charge();

					virtual void UpdateStageActor() override;

				private:
					int mCnt;
				};


				class Zyu : public StageActor
				{
				public:
					Zyu(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
					virtual ~Zyu();

					virtual void UpdateStageActor() override;

				private:
					int mCnt;
				};

				class Line : public StageActor
				{
				public:
					Line(StageScene* scene, const GameLib::Vector2& pos,bool isRight, int updateOrder = 0);
					virtual ~Line();

					virtual void UpdateStageActor() override;

				private:
					RectangleComponent* mRect;
					Body* mBody[4];
					int mCnt;
				};
			}

		}

	}
}