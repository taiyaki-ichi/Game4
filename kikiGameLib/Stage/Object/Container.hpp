#pragma once
#include"Stage/StageActor.hpp"

namespace GameLib
{
	class TextureComponent;
}

namespace Game
{
	namespace Stage
	{
		class Body;

		class Container : public StageActor
		{
		public:
			Container(StageScene* scene, const GameLib::Vector2& pos, int UupdateOrder = 0);
			virtual ~Container();

			static const float GRAVITY;
			static const float SPEED;

			virtual void UpdateStageActor() override;
			virtual void Hit(Body* myBody, Body* theBody) override;

		private:
			Body* mBody;
			GameLib::TextureComponent* mTexture;
			bool mOnGround;
			int mPlayerPosFlag;
			
		};

	}
}