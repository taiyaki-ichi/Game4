#pragma once
#include"StageStateActor.hpp"
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

		class Player : public StageStateActor
		{
		public:
			Player(StageScene* scene,const GameLib::Vector2& pos);
			virtual ~Player();

			GameLib::AnimComponent* GetAnim() const { return mAnim; }
			GameLib::AnimComponent* GetSubAnim() const { return mSubAnim; }

			void BreakBody();

		private:

			Body* mBody;
			GameLib::AnimComponent* mAnim;
			GameLib::AnimComponent* mSubAnim;


		};


		namespace PlayerState
		{

			namespace PlayerMode
			{
				class Mode;
			}

			class Active : public StageState
			{
			public:
				enum class Motion {
					Stay,
					Run,
					Down,
					Up
				};

				enum class Dir {
					Right,
					Left
				};

				const float MAX_SPEED = 6.5f;
				const float GRAVITY = 0.7f;
				const float JUMPING_GRAVITY = 0.4f;
				const float JUMP_POWER_MAX = 11.5f;
				const float JUMP_POWER_MIN = 9.5f;
				const float RUN_POWER = 0.2;

				Active(Player* player);
				virtual ~Active();

				virtual StageState* Update() override;
				virtual void Input(const GameLib::InputState& state) override;
				virtual void Hit(Body* myBody, Body* theBody) override;

			private:
				Player* mPlayer;

				GameLib::Vector2 mVelocity;

				Motion mMotion;
				Dir mDir;

				PlayerMode::Mode* mMode;
				void SetMode(PlayerMode::Mode* mode);

				//�W�����v�ł��邩�ǂ���
				bool mJumpFlag;
				//�W�����v�����ǂ���
				bool mIsJumping;
				//�W�����v����̉����x�������邩�ǂ���
				bool mJumpAcceleFlag;

				//�n�ʂɂ��Ă��邩�ǂ���
				bool mIsOnGround;

				//���SState�ɍs�����ǂ���
				bool mDeathFlag;

				//�G�𓥂񂾎��̃W�����v
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


			namespace PlayerMode
			{
				class Mode
				{
				public:
					Mode(Player* player);
					virtual ~Mode();

					virtual void Update() final;

					bool IsTranceformed();

					virtual void UpdateMode() = 0;
					virtual void Action() = 0;

				protected:
					Player* mPlayer;
					int mTranceformCnt;
				};

				class Nomal : public Mode
				{
				public:
					Nomal(Player* player);
					virtual ~Nomal();

					virtual void UpdateMode() override;
					virtual void Action() override;
				};

				class Cock : public Mode
				{
				public:
					Cock(Player* player);
					virtual ~Cock();

					virtual void UpdateMode() override;
					virtual void Action() override;
	
				};

				class Wizard : public Mode
				{
				public:
					Wizard(Player* player);
					virtual ~Wizard();

					virtual void UpdateMode() override;
					virtual void Action() override;
				};

				class Alien : public Mode
				{
				public:
					Alien(Player* plaeyer);
					virtual ~Alien();

					virtual void UpdateMode() override;
					virtual void Action() override;
				};

			}


		}

	}
}