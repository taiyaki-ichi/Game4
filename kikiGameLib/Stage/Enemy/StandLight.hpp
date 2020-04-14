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

			namespace StandLightParts
			{
				class Head;
			}

			class StandLight : public StageActor
			{
			public:

				StandLight(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~StandLight();

				virtual void UpdateStageActor() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

				void HeadDead() { mHeadDeathFlag = true; }

			private:
				GameLib::AnimComponent* mAnim;
				Body* mStemBody;

				StandLightParts::Head* mHead;

				int mCnt;

				bool mHeadDeathFlag;

			};

			namespace StandLightParts
			{
				constexpr float ACTIVERANGE = 400.f;

				class Head : public StageStateActor
				{
				public:

					Head(StageScene* scene, StandLight* stem, const GameLib::Vector2& pos, int updateOeder = 0);
					virtual ~Head();

					GameLib::AnimComponent* GetAnim() const { return mAnim; }
					void BreakBody();
					Body* GetBody() const { return mBody; }

					void HeadDead();

				private:
					StandLight* mStem;

					Body* mBody;
					GameLib::AnimComponent* mAnim;

				};

				class HeadActive : public StageState
				{
				public:
					HeadActive(Head* head);
					virtual ~HeadActive();

					static const int BEAMTIME;
					static const int COOLTIME;

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					Head* mHead;
					int mCnt;
				};

				class HeadSleep : public StageState
				{
				public:
					HeadSleep(Head* head);
					virtual ~HeadSleep();

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					Head* mHead;
				};

				class HeadDeath : public StageState
				{
				public:
					HeadDeath(Head* head);
					virtual ~HeadDeath();

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					Head* mHead;
					int mCnt;
				};

				void ActiveAndSleepHit(Head* head,Body* myBody, Body* theBody);

				class Spore : public StageActor
				{
				public:
					Spore(StageScene* scene, const GameLib::Vector2& pos, const GameLib::Vector2& velocity, int updateOrder = 0);
					virtual ~Spore();

					virtual void UpdateStageActor() override;

				private:
					GameLib::Vector2 mVelocity;
				};
			}

		}
	}
}