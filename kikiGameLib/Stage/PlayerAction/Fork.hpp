#pragma once
#include"Stage/StageStateActor.hpp"

namespace GameLib
{
	class TextureComponent;
}


namespace Game
{
	namespace Stage
	{
		class Body;

		namespace PlayerAction
		{
			class Fork : public StageStateActor
			{
			public:
				Fork(StageScene* scene, const GameLib::Vector2& pos,bool IsRight ,int updateOrder = 0);
				virtual ~Fork();

				Body* GetBody() const { return mBody; }

			private:
				Body* mBody;
			};


			class ForkActive : public StageState
			{
			public:
				ForkActive(Fork* fork,bool IsRight);
				virtual ~ForkActive();

				virtual StageState* Update() override;
				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				Fork* mFork;

				//Forkê∂ê¨éûÅAínñ Ç∆ê⁄êGÇµÇƒÇ¢ÇÈÇÃÇ»ÇÁê∂ê¨Ç≥ÇπÇ»Ç¢ÇÊÇ§
				int mCnt;

				bool mIsRight;

			};

			class ForkFall : public StageState
			{
			public:
				ForkFall(Fork* fork, bool isRigjht);
				virtual ~ForkFall();

				virtual StageState* Update() override;

			private:
				Fork* mFork;
				float mAdRot;
			};

			class ForkGround : public StageState
			{
			public:
				ForkGround(Fork* fork, bool isRight,Body* groundBody);
				virtual ~ForkGround();

				virtual StageState* Update() override;

			private:
				Fork* mFork;
				bool mIsRight;
				Body* mGroundBody;
				int mCnt;
			};

		}
	}
}