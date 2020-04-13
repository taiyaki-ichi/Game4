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

		class Container : public StageStateActor
		{
		public:
			Container(StageScene* scene, const GameLib::Vector2& pos, int UupdateOrder = 0);
			virtual ~Container();

			void BreakBody();
			Body* GetBody() const { return mBody; }

		private:
			Body* mBody;
			GameLib::TextureComponent* mTexture;
			
		};

		class ContainerActive : public StageState
		{
		public:
			ContainerActive(Container* contaner);
			virtual ~ContainerActive();

			static const float GRAVITY;
			static const float SPEED;

			virtual StageState* Update() override;
			virtual void Hit(Body* myBody, Body* theBody) override;

		private:
			Container* mContainer;
			bool mOnGround;

			int mGroundTimeCnt;
			
		};

	}
}