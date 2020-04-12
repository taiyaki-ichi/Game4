#pragma once
#include"Stage/StageStateActor.hpp"

namespace GameLib
{
	class AnimComponent;
	class Vector2;
}

namespace Game
{
	namespace Stage
	{
		class Body;

		namespace Enemy
		{

			class Toge : public StageStateActor
			{
			public:
				Toge(StageScene* scene,const GameLib::Vector2& pos);
				virtual ~Toge();

				void BreakBody();
				GameLib::AnimComponent* GetAnim() const { return mAnim; }

			private:
			
				GameLib::AnimComponent* mAnim;
				Body* mBody;

			};

			class TogeActive : public StageState
			{
			public:
				TogeActive(Toge* toge);
				virtual ~TogeActive();

				virtual StageState* Update() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				Toge* mToge;
				float mTimer;
			};
			
		}
	}
}