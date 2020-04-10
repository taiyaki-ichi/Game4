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

			class Triple : public StageStateActor
			{
			public:
				Triple(StageScene* scene, const GameLib::Vector2& pos);
				virtual ~Triple();

				void SetAnimChannel(int i);
				int GetAnimCannel() const;

				void BreakBody();

			private:

				GameLib::AnimComponent* mAnim;

				Body* mBody;
				Body* mWeakness;

			};



			class TripleActive : public StageState
			{
			public:
				TripleActive(Triple* triple);
				virtual ~TripleActive();

				virtual StageState* Update() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

				float GetVelocity() const { return mVelocity; };

			private:
				Triple* mTriple;
				float mVelocity;

				bool mFlatFlag;
			};



		}
	}
}