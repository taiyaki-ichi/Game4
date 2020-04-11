#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		class RectangleComponent;
		class Body;

		namespace PlayerAction
		{

			class Meteor : public StageActor
			{
			public:
				Meteor(StageScene* scene, float x, int upateOrder = 0);
				virtual ~Meteor();

				virtual void UpdateStageActor() override;

			private:
				RectangleComponent* mRect;
				Body* mBody;
				int mCnt;
			};
		}
	}
}