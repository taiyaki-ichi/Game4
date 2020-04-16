#pragma once
#include"Stage/StageStateActor.hpp"

namespace GameLib
{
	class AnimComponent;
	class TextureComponent;
}

namespace Game
{
	namespace Stage
	{
		class Body;

		namespace Enemy
		{

			class Maimai : public StageStateActor
			{
			public:
				Maimai(StageScene* scene, const GameLib::Vector2& pos, int udpdateOrder = 0);
				virtual ~Maimai();

				GameLib::AnimComponent* GetAnim() const { return mAnim; }
				void BreakBody();

			private:
				GameLib::AnimComponent* mAnim;
				Body* mBody;
				Body* mWeakness;
			};

			namespace MaimaiState
			{
				class Active : public StageState
				{
				public:
					Active(Maimai* m);
					virtual ~Active();

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					int mCnt;
					Maimai* mMaimai;
				};
			}

			class Nail : public StageStateActor
			{
			public:
				Nail(StageScene* scene, const GameLib::Vector2& pos,bool isRignt, int updateOrder = 0);
				virtual ~Nail();

				void BreakBody();

			private:
				GameLib::TextureComponent* mTexture;
				Body* mBody;
				Body* mWeakness;
			};

			namespace NailState
			{
				class Active : public StageState
				{
				public: 
					Active(Nail* n,bool isRight);
					virtual ~Active();

					virtual StageState* Update() override;
					virtual void Hit(Body* myBody, Body* theBody) override;

				private:
					Nail* mNail;
					bool mIsRight;
				};
			}
		}
	}
}