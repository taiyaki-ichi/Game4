#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{

		//コースの端では使用できない
		class Warp : public StageActor
		{
		public:
			Warp(StageScene* scene, const GameLib::Vector2& pos, int updateOrder=0);
			virtual ~Warp();

			static float SPEED;

			virtual void UpdateStageActor();
			virtual void Hit(Body* myBody, Body* theBody) override;

			void SetTarget(Warp* w) { mTarget = w; }
			void GoPlayer() { mCnt = 0; }

		private:
			Warp* mTarget;
			int mCnt;

			StageActor* mPlayer;
			Body* mPlayerBody;
		};
	}
}