#pragma once
#include"StageActor.hpp"
#include"StageState.hpp"
namespace GameLib
{
	class AnimComponent;
	class InputState;

}
namespace Game
{

	namespace Stage
	{
		class Body;
		namespace PlayerState
		{
			class State;
		}

		class Player : public StageActor
		{
		public:
			Player(StageScene* scene,const GameLib::Vector2& pos);
			virtual ~Player();

			void UpdateStageActor() override;
			void Hit(Body* myBody, Body* theBody) override;
			void Input(const GameLib::InputState& state) override;

			GameLib::AnimComponent* GetAnim() const { return mAnim; }
			GameLib::AnimComponent* GetSubAnim() const { return mSubAnim; }

			void BreakBody();

		private:
			StageState* mState;
			Body* mBody;
			GameLib::AnimComponent* mAnim;
			GameLib::AnimComponent* mSubAnim;


		};


		namespace PlayerState
		{

			class Active : public StageState
			{
			public:
				enum class Motion {
					Stay,
					Run,
					Down,
					Up
				};
				enum class Mode {
					Nomal = 0,
					Witch = 2,
					Cock = 4,
					Alien = 6,
				};
				enum class Dir {
					Right,
					Left
				};

				const float MAX_SPEED = 5.f;
				const float GRAVITY = 0.6f;
				const float JUMPING_GRAVITY = 0.4f;
				const float JUMP_POWER_MAX = 11.5f;
				const float JUMP_POWER_MIN = 10.5f;
				const float RUN_POWER = 0.25;

				Active(Player* player);
				virtual ~Active();

				virtual StageState* Update() override;
				virtual void Input(const GameLib::InputState& state) override;
				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				Player* mPlayer;

				GameLib::Vector2 mVelocity;

				Motion mMotion;
				Mode mMode;
				Dir mDir;

				//ジャンプできるかどうか
				bool mJumpFlag;
				//ジャンプ中かどうか
				bool mIsJumping;
				//ジャンプ直後の加速度を加えるかどうか
				bool mJumpAcceleFlag;

				//地面についているかどうか
				bool mIsOnGround;

				//変身モーションの時間
				int mTransformCnt;

				GameLib::Vector2 mGroundVelocity;

				//死亡Stateに行くかどうか
				bool mDeathFlag;

				//敵を踏んだ時のジャンプ
				unsigned int mJumpFlag2;
			};
			
			class Death : public StageState
			{
			public:
				Death(Player* player);
				virtual ~Death();

				virtual StageState* Update() override;

			private:
				Player* mPlayer;

			};

		}

	}
}