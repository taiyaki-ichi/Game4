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
			class Missile;

			class MissileBody : public StageActor
			{
			public:
				MissileBody(StageScene* scene, Missile* mi, int updateOrder = 0);
				virtual ~MissileBody();

				virtual void UpdateStageActor() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				Body* mBody;
				Body* mWeakness;
				Missile* mMissile;
			};

			class Missile : public StageStateActor
			{
			public: 
				Missile(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Missile();

				GameLib::AnimComponent* GetAnim() const { return mAnim; }

			private:
				MissileBody* mBody;
				GameLib::AnimComponent* mAnim;

			};

			namespace MissileState
			{

				class Stay : public StageState
				{
				public:
					Stay(Missile* m);
					virtual ~Stay();

					virtual StageState* Update()override;

				private:
					Missile* mMissile;
				};

				class Active : public StageState
				{
				public:
					Active(Missile* mi);
					virtual ~Active();

					virtual StageState* Update() override;

				private:
					Missile* mMissile;
				};

				class Go : public StageState
				{
				public:
					Go(Missile* m, bool isDown);
					virtual ~Go();

					StageState* Update() override;

				private:
					bool mIsDown;
					Missile* mMissle;

				};
			}

		}
	}
}
