#include"Player.hpp"
#include"CollisionDetection/Body.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/InputState.hpp"
#include"WindowData.hpp"
#include"StageScene.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		using Vec2 = GameLib::Vector2;


		Player::Player(StageScene* scene, const GameLib::Vector2& pos)
			:StageActor(scene)
		{
			scene->SetPlayer(this);
			
			SetScale(0.1f);
			SetPosition(pos);
			

			mBody = new Body(this, "Player");
			mBody->SetWidthAndHeight(250.f, 500.f);
			mBody->SetAdjust(Vec2(0.f, 120.f));
			mBody->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));
			
			
			using Anim = std::vector<GameLib::Texture*>;
			using Data = GameLib::Data;
			Anim run = {
				Data::GetTexture("Assets/tama/run001.png"),
				Data::GetTexture("Assets/tama/run002.png"),
				Data::GetTexture("Assets/tama/run003.png"),
				Data::GetTexture("Assets/tama/run002.png"),
			};
			Anim stay = {
				Data::GetTexture("Assets/tama/stay001.png")
			};
			Anim down = {
				Data::GetTexture("Assets/tama/down.png"),
			};
			Anim up = {
				Data::GetTexture("Assets/tama/up.png"),
			};
			Anim death = {
				Data::GetTexture("Assets/tama/death.png"),
			};

			std::vector<Anim> anims = {
				stay,
				run,
				up,
				down,
				death,
			};

			mAnim = new GameLib::AnimComponent(this, anims);
			mAnim->SetChannel(0);
			mAnim->SetAnimFPS(10);
			
			Anim nomal = {
				Data::GetTexture("Assets/tomei.png"),
			};
			Anim angel = {
				Data::GetTexture("Assets/tama/angel.png"),
			};
			Anim witch1 = {
				Data::GetTexture("Assets/tama/witch.png"),
			};
			Anim witch2 = {
				Data::GetTexture("Assets/tama/witch.png"),
				Data::GetTexture("Assets/tomei.png"),
			};
			Anim cock1 = {
				Data::GetTexture("Assets/tama/cock.png"),
			};
			Anim cock2 = {
				Data::GetTexture("Assets/tama/cock.png"),
				Data::GetTexture("Assets/tomei.png"),
			};
			Anim alien1 = {
				Data::GetTexture("Assets/tama/alien.png"),
			};
			Anim alien2 = {
				Data::GetTexture("Assets/tama/alien.png"),
				Data::GetTexture("Assets/tomei.png"),
			};

			std::vector<Anim> sub = {
				nomal,
				angel,
				witch1,
				witch2,
				cock1,
				cock2,
				alien1,
				alien2,
			};
			mSubAnim = new GameLib::AnimComponent(this, sub);
			mSubAnim->SetChannel(0);
			
			mState = new PlayerState::Active(this);

			std::cout << "Player\nPos :" << pos.x << "," << pos.y << "\n";
			
		}

		Player::~Player()
		{
		}

		void Player::UpdateStageActor()
		{
			
			StageState* next = mState->Update();
			if (next != mState)
			{
				delete mState;
				mState = next;
			}
			
		}

		void Player::Hit(Body* myBody, Body* theBody)
		{
			mState->Hit(myBody, theBody);
		}

		void Player::Input(const GameLib::InputState& state)
		{
			mState->Input(state);
		}


		PlayerState::Active::Active(Player* player)
			:StageState()
			,mPlayer(player)
			,mVelocity()
			,mMode(Mode::Nomal)
			,mMotion(Motion::Stay)
			,mDir(Dir::Right)
			,mJumpFlag(false)
			,mIsJumping(false)
			,mJumpAcceleFlag(false)
			,mTransformCnt(-1)
		{
		}
		PlayerState::Active::~Active()
		{
		}

		StageState* PlayerState::Active::Update()
		{

			Vec2 pos = mPlayer->GetPosition();

			//重力
			//ジャンプボタンを押しているかどうかで変化
			if (mIsJumping == true)
				mVelocity.y += JUMPING_GRAVITY;
			else
				mVelocity.y += GRAVITY;
	
			
			//Playerの向きによって画像の向きを変化さす
			if (mDir == Dir::Right)
			{
				mPlayer->GetAnim()->SetTextureFlip(GameLib::TextureFlip::None);
				mPlayer->GetSubAnim()->SetTextureFlip(GameLib::TextureFlip::None);
			}
			else
			{
				mPlayer->GetAnim()->SetTextureFlip(GameLib::TextureFlip::Horizontal);
				mPlayer->GetSubAnim()->SetTextureFlip(GameLib::TextureFlip::Horizontal);
			}
			
			//サブのアニメの変化
			if (mTransformCnt >= 0)
			{
				mPlayer->GetSubAnim()->SetChannel(static_cast<int>(mMode) + 1);
				mTransformCnt++;
				if (mTransformCnt >= 40)
					mTransformCnt = -1;
			}
			else
				mPlayer->GetSubAnim()->SetChannel(static_cast<int>(mMode));


			//ジャンプの加速度の計算
			if (mJumpAcceleFlag == true)
			{
				mVelocity.y = 0.f;
				float rate = GameLib::Math::Abs(mVelocity.x) / MAX_SPEED;
				float jumpadjust = (JUMP_POWER_MAX - JUMP_POWER_MIN) * rate;
				mVelocity.y -= JUMP_POWER_MIN + jumpadjust;

				mJumpAcceleFlag = false;
			}

			//ヨコの加速度
			if (mMotion == Motion::Run)
			{
				if (mDir == Dir::Right)
				{
					mVelocity.x += RUN_POWER;
				}
				else
				{
					mVelocity.x -= RUN_POWER;
				}
			}

			//速度の計算
			if (mMotion == Motion::Stay) {
				if (mIsOnGround == true)
				{
					mVelocity.x *= 0.8f;
				}
				else
				{
					mVelocity.x *= 0.98f;
				}
			}
			//速度の調整
			if (mVelocity.x < -MAX_SPEED) {
				mVelocity.x = -MAX_SPEED;
			}
			else if (mVelocity.x > MAX_SPEED) {
				mVelocity.x = MAX_SPEED;
			}
			if (mVelocity.y < -MAX_SPEED * 2.f) {
				mVelocity.y = -MAX_SPEED * 2.f;
			}
			else if (mVelocity.y > MAX_SPEED * 2.f) {
				mVelocity.y = MAX_SPEED * 2.f;
			}

			//位置の更新
			pos += mVelocity;

			//落下中のアニメーション
			if (mIsOnGround == false) {
				if (mPlayer->GetPosition().y > pos.y) {
					mMotion = Motion::Down;
				}
				else if (mPlayer->GetPosition().y < pos.y) {
					mMotion = Motion::Up;
				}
			}


			mPlayer->GetAnim()->SetChannel(static_cast<int>(mMotion));

			//落下死
			if (pos.y > WINDOW_HEIGHT + 100.f)
			{
				//return DathState
			}

			mPlayer->SetPosition(pos);

			mJumpAcceleFlag = false;
			mJumpFlag = false;
			mIsOnGround = false;


			return this;
		}

		void PlayerState::Active::Input(const GameLib::InputState& state)
		{

			mMotion = Motion::Stay;

			using Key = GameLib::Key;
			using ButtonState = GameLib::ButtonState;
			if (state.GetState(Key::A) == ButtonState::Pressed &&
				state.GetState(Key::D) == ButtonState::Pressed)
			{

			}
			else if (state.GetState(Key::A) == ButtonState::Pressed)
			{
				mDir = Dir::Left;
			}
			else if (state.GetState(Key::D) == ButtonState::Pressed)
			{
				mDir = Dir::Right;
			}
			else if (state.GetState(Key::A) == ButtonState::Held &&
				state.GetState(Key::Down) == ButtonState::Held)
			{

			}
			else if (state.GetState(Key::A) == ButtonState::Held)
			{
				mDir = Dir::Left;
			}
			else if (state.GetState(Key::D) == ButtonState::Held)
			{
				mDir = Dir::Right;
			}

			if (state.GetState(Key::A) == ButtonState::Held ||
				state.GetState(Key::D) == ButtonState::Held) {
				mMotion = Motion::Run;
			}

			if (state.GetState(Key::A) == ButtonState::Released ||
				state.GetState(Key::D) == ButtonState::Released) {
				mMotion = Motion::Stay;
			}

			if (mJumpFlag == true )
			{
				if (state.GetState(Key::Space) == ButtonState::Pressed) {
					mIsJumping = true;
					mJumpFlag = false;
					mJumpAcceleFlag = true;
					mVelocity.y = 0.f;

				}
			}
			if (state.GetState(Key::Space) == ButtonState::Released && mVelocity.y < 0.f)
			{
				mIsJumping = false;
			}

			if (state.GetState(Key::J) == ButtonState::Pressed )
			{
				/*
				if (mMode == Mode::Cock)
					Fork* fork = new Fork(GetStageScene(), this);

				if (mMode == Mode::Witch)
					Meteor* meteor = new Meteor(GetStageScene(), this);

				if (mMode == Mode::Alien)
					Beam* b = new Beam(GetStageScene(), this);
					*/
			}

		}

		void PlayerState::Active::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Ground")
			{
				using Vec2 = GameLib::Vector2;
				Vec2 myPos = myBody->GetOwner()->GetPosition() + myBody->GetAdjust();
				Vec2 groundPos = theBody->GetOwner()->GetPosition();
				float mH = myBody->GetHeight();
				float gH = theBody->GetHeight();
				float l = groundPos.y - myPos.y;
				float d = gH / 2.f + mH / 2.f - l;
				
				myPos.y -= d + myBody->GetAdjust().y;
				myBody->GetOwner()->SetPosition(myPos);

				mVelocity.y = 0.f;
				mJumpFlag = true;
				mIsOnGround = true;
				mIsJumping = false;
			}


		}



	}
}

