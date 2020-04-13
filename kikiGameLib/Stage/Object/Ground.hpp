#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		class Body;
		class StageScene;
		
		class Ground : public StageActor
		{
		public:
			Ground(StageScene* scene,const GameLib::Vector2& pos, float width, float height, int updateOrder = 0);
			virtual ~Ground();

			virtual void UpdateStageActor() override final;
			virtual void UpdateGround() {}

			virtual void Hit(Body* myBody, Body* theBody) override;

			void IsUnbreakable() { mIsUnbreakable = true; }

			void BreakNextUpdate() { mBreakFlag = true; }
			bool GetBreakFlag() const { return mBreakFlag; }

			//beam‚Å‰ó‚³‚ê‚½‚Æ‚«—p
			virtual void CreateGround(const GameLib::Vector2& pos, float w, float h);

		private:
			Body* mBody;
			bool mBreakFlag;
			bool mIsUnbreakable;
		};


		class MoveGround : public Ground
		{
		public:
			MoveGround(StageScene* scene, const GameLib::Vector2& p1, const GameLib::Vector2& p2, float width, float height, int updateOrder = 0);
			virtual ~MoveGround();

			static const float SPEED;

			virtual void UpdateGround() override;
			virtual void AdjustPosSub(const GameLib::Vector2& vec) override;
			virtual void CreateGround(const GameLib::Vector2& pos, float w, float h)override;

			void SetVelocity(const GameLib::Vector2& vec) { mVelocity = vec; }

		private:
			GameLib::Vector2 mVelocity;

			GameLib::Vector2 mPoint1;
			GameLib::Vector2 mPoint2;
		};
		
		void BeamHit(Ground* myGround, Body* myBody, Body* theBody);

	}
}