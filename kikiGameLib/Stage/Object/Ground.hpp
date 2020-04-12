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

		
		void BeamHit(Ground* myGround, Body* myBody, Body* theBody);

	}
}