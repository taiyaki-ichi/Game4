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

			void UpdateStageActor() override;

			void SetVelocity(const GameLib::Vector2& v) { mVelocity = v; }
			const GameLib::Vector2& GetVelocity() const { return mVelocity; }

		private:
			GameLib::Vector2 mVelocity;
			Body* mBody;
		};
	}
}