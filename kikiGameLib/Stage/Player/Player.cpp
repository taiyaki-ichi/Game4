#include"Player.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/InputState.hpp"
#include"WindowData.hpp"
#include"Stage/StageScene.hpp"
#include"Action/Fork.hpp"
#include"Action/Meteor.hpp"
#include"Action/Beam.hpp"
#include"PlayerLife.hpp"
#include"Stage/Score/ScoreBoard.hpp"
#include"Action/Assist.hpp"
#include"Stage/Object/Trampoline.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		using Vec2 = GameLib::Vector2;


		Player::Player(StageScene* scene, const GameLib::Vector2& pos )
			:StageStateActor(scene,pos)
		{
			scene->SetPlayer(this);
			
			SetScale(0.1f);
			
			mBody = new Body(this, "Player");
			mBody->SetWidthAndHeight(250.f, 500.f);
			mBody->SetAdjust(Vec2(0.f, 120.f));
			mBody->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));
			
			
			using Anim = std::vector<GameLib::Texture*>;
			using Data = GameLib::Data;
			Anim run = {
				Data::GetTexture("../Assets/tama/run001.png"),
				Data::GetTexture("../Assets/tama/run002.png"),
				Data::GetTexture("../Assets/tama/run003.png"),
				Data::GetTexture("../Assets/tama/run002.png"),
			};
			Anim stay = {
				Data::GetTexture("../Assets/tama/stay001.png")
			};
			Anim down = {
				Data::GetTexture("../Assets/tama/down.png"),
			};
			Anim up = {
				Data::GetTexture("../Assets/tama/up.png"),
			};

			Anim runSub = {
				Data::GetTexture("../Assets/tama/run001.png"),
				Data::GetTexture("../Assets/tomei.png"),
				Data::GetTexture("../Assets/tama/run002.png"),
				Data::GetTexture("../Assets/tomei.png"),
				Data::GetTexture("../Assets/tama/run003.png"),
				Data::GetTexture("../Assets/tomei.png"),
				Data::GetTexture("../Assets/tama/run002.png"),
				Data::GetTexture("../Assets/tomei.png"),
			};
			Anim staySub = {
				Data::GetTexture("../Assets/tama/stay001.png"),
				Data::GetTexture("../Assets/tomei.png"),
			};
			Anim downSub = {
				Data::GetTexture("../Assets/tama/down.png"),
				Data::GetTexture("../Assets/tomei.png"),
			};
			Anim upSub = {
				Data::GetTexture("../Assets/tama/up.png"),
				Data::GetTexture("../Assets/tomei.png"),
			};

			Anim death = {
				Data::GetTexture("../Assets/tama/death.png"),
			};
			

			std::vector<Anim> anims = {
				stay,
				run,
				up,
				down,
				death,
				staySub,
				runSub,
				upSub,
				downSub,

			};

			mAnim = new GameLib::AnimComponent(this, anims);
			mAnim->SetChannel(0);
			mAnim->SetAnimFPS(10);
			mAnim->SetDrawOrder(100);
			
			Anim nomal = {
				Data::GetTexture("../Assets/tomei.png"),
			};
			Anim angel = {
				Data::GetTexture("../Assets/tama/angel.png"),
			};
			Anim witch1 = {
				Data::GetTexture("../Assets/tama/witch.png"),
			};
			Anim witch2 = {
				Data::GetTexture("../Assets/tama/witch.png"),
				Data::GetTexture("../Assets/tomei.png"),
			};
			Anim cock1 = {
				Data::GetTexture("../Assets/tama/cock.png"),
			};
			Anim cock2 = {
				Data::GetTexture("../Assets/tama/cock.png"),
				Data::GetTexture("../Assets/tomei.png"),
			};
			Anim alien1 = {
				Data::GetTexture("../Assets/tama/alien.png"),
			};
			Anim alien2 = {
				Data::GetTexture("../Assets/tama/alien.png"),
				Data::GetTexture("../Assets/tomei.png"),
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
			mSubAnim->SetAnimFPS(10);
			mSubAnim->SetDrawOrder(110);
			
			SetStageState(new PlayerState::Active(this));

		
			mLife = new PlayerLife(scene, this);
		}

		Player::~Player()
		{
		}

		void Player::BreakBody()
		{
			mBody->SetWidthAndHeight(0.f, 0.f);
		}


		PlayerState::Active::Active(Player* player)
			:StageState()
			, mPlayer(player)
			, mVelocity()
			, mMotion(Motion::Stay)
			, mDir(Dir::Right)
			, mJumpFlag(false)
			, mIsJumping(false)
			, mJumpAcceleFlag(false)
			, mJumpFlag2(0)
			, mCrushedFlag(false)
			,mIsOnGround(false)
		{
			mMode = new PlayerMode::Nomal(mPlayer);
		}



		PlayerState::Active::~Active()
		{
			if (mMode)
				delete mMode;
			
			
		}

		StageState* PlayerState::Active::Update()
		{
			//今のところActiveな状態でBodyのタテヨコが0.fになるのはWarpの時のみ
			if (mPlayer->GetBody()->GetHeight() > 0.f && mPlayer->GetBody()->GetWidth() > 0.f)
			{
				if (mCrushedFlag && mIsOnGround)
					return new Death(mPlayer);

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

				//ジャンプの加速度の計算
				if (mJumpAcceleFlag == true)
				{
					//mVelocity.y = 0.f;
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
						if (mVelocity.x < 0.f)
							mVelocity.x += RUN_POWER * 2.f;
						else
							mVelocity.x += RUN_POWER;
					}
					else
					{
						if (mVelocity.x > 0.f)
							mVelocity.x -= RUN_POWER * 2.f;
						else
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
				if (mVelocity.y < -MAX_SPEED * 4.f) {
					mVelocity.y = -MAX_SPEED * 4.f;
				}
				else if (mVelocity.y > MAX_SPEED * 4.f) {
					mVelocity.y = MAX_SPEED * 4.f;
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


				if (mPlayer->GetLife()->GetInvincibleFlag())
					mPlayer->GetAnim()->SetChannel(static_cast<int>(mMotion) + 5);
				else
					mPlayer->GetAnim()->SetChannel(static_cast<int>(mMotion));


				//落下死
				if (pos.y > WINDOW_HEIGHT + 100.f)
				{
					return new PlayerState::Death(mPlayer);
				}

				mPlayer->SetPosition(pos);


				//状態の更新
				if (mMode)
					mMode->Update();


				//敵を踏んでいる最中の処理
				if (mJumpFlag2 > 0)
				{
					mJumpFlag2 -= 1;
				}



				mJumpAcceleFlag = false;
				mJumpFlag = false;
				mIsOnGround = false;
				mCrushedFlag = false;

			}
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

			if (mJumpFlag == true ||mJumpFlag2 > 0)
			{
				if (state.GetState(Key::Space) == ButtonState::Pressed) {
					mIsJumping = true;
					mJumpFlag = false;
					mJumpAcceleFlag = true;
					//mVelocity.y = 0.f;
					mJumpFlag2 = 0;
				}
			}
			if (state.GetState(Key::Space) == ButtonState::Released && mVelocity.y < 0.f)
			{
				mIsJumping = false;
			}

			if (state.GetState(Key::J) == ButtonState::Pressed )
			{
				if (mMode)
					mMode->Action();
			}

		}

		void PlayerState::Active::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Ground")
			{
				using Vec2 = GameLib::Vector2;
				Vec2 pos = myBody->GetOwner()->GetPosition();
				Vec2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, MAX_SPEED);


				if (adjust.x < 0.f && mVelocity.x>0.f)
				{
					mVelocity.x = 0.f;
				}
				if (adjust.x > 0.f && mVelocity.x < 0.f)
				{
					mVelocity.x = 0.f;
				}
				if (adjust.y < 0.f && mVelocity.y>0.f) {
					mVelocity.y = 0.f;
					mJumpFlag = true;
					mIsOnGround = true;
					mIsJumping = false;

					adjust += theBody->GetVelocity();
				}
				if (adjust.y > 0.f && mVelocity.y < 0.f)
				{
					mVelocity.y = 0.f;
					mIsJumping = false;
				}

				if (adjust.y > 20.f)
					mCrushedFlag = true;

				myBody->GetOwner()->SetPosition(pos + adjust);
			}
			else if (name == "ItemCock")
			{
				theBody->GetOwner()->SetState(GameLib::Actor::State::Dead);
				SetMode(new PlayerMode::Cock(mPlayer));
				new ActionAssist(mPlayer);
			}
			else if (name == "ItemWizard")
			{
				theBody->GetOwner()->SetState(GameLib::Actor::State::Dead);
				SetMode(new PlayerMode::Wizard(mPlayer));
				new ActionAssist(mPlayer);
			}
			else if (name == "ItemAlien")
			{
				theBody->GetOwner()->SetState(GameLib::Actor::State::Dead);
				SetMode(new PlayerMode::Alien(mPlayer));
				new ActionAssist(mPlayer);
			}
			else if (name == "ForkGround")
			{
				Vec2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, MAX_SPEED);
				if (mVelocity.y > 0.f && adjust.y < 0.f)
				{
					Vec2 pos = myBody->GetOwner()->GetPosition();

					mVelocity.y = 0.f;
					mJumpFlag = true;
					mIsOnGround = true;
					mIsJumping = false;
					adjust += theBody->GetVelocity();

					myBody->GetOwner()->SetPosition(pos + adjust);
				}
			}
			else if ((name == "Meteor" && !mPlayer->GetLife()->GetInvincibleFlag()) ||
				(name == "Beam" && !mPlayer->GetLife()->GetInvincibleFlag()))
			{
				mPlayer->SetStageState(new PlayerState::Death(mPlayer));
			}
			else if (name == "Container")
			{
				Vec2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, MAX_SPEED);
				if (GameLib::Math::Abs(adjust.x) > 0.f)
				{
					mVelocity.x *= 0.7f;
					theBody->GetOwner()->SetPosition(theBody->GetOwner()->GetPosition() - adjust);

				}
				else
				{
					if (adjust.y < 0.f && mVelocity.y>0.f) {
						mVelocity.y = 0.f;
						mJumpFlag = true;
						mIsOnGround = true;
						mIsJumping = false;

						adjust += theBody->GetVelocity();
					}
					else if (adjust.y > 0.f && mVelocity.y < 0.f)
					{
						mVelocity.y = 0.f;
						mIsJumping = false;

					}

					if (adjust.y > 20.f)
						mCrushedFlag = true;
					myBody->GetOwner()->SetPosition(myBody->GetOwner()->GetPosition() + adjust);
				}
			}
			else if (name == "Heart")
			{
				theBody->GetOwner()->SetState(GameLib::Actor::State::Dead);
				mPlayer->GetLife()->Heal();
			}
			else if (name == "Goal")
			{
				mPlayer->SetStageState(new PlayerState::Goal(mPlayer, theBody->GetOwner()->GetPosition(), mVelocity));
			}
			else if (name == "Tear")
			{
				theBody->GetOwner()->SetState(GameLib::Actor::State::Dead);
				theBody->SetWidthAndHeight(0.f, 0.f);
				mPlayer->GetStageScene()->GetTear();

			}
			else if (name == "Diamond")
			{
				theBody->GetOwner()->SetState(GameLib::Actor::State::Dead);
				theBody->SetWidthAndHeight(0.f, 0.f);
				mPlayer->GetStageScene()->GetDiamond();

			}
			else if (name == "Trampoline")
			{
				using Vec2 = GameLib::Vector2;
				Vec2 pos = myBody->GetOwner()->GetPosition();
				Vec2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, MAX_SPEED);


				if (adjust.x < 0.f && mVelocity.x>0.f)
				{
					mVelocity.x = 0.f;
				}
				if (adjust.x > 0.f && mVelocity.x < 0.f)
				{
					mVelocity.x = 0.f;
				}
				if (adjust.y < 0.f && mVelocity.y>0.f) {
					mVelocity.y = -Trampoline::PLAYERPOWER;
					mJumpFlag2 = 4;
					mIsOnGround = true;
					mIsJumping = false;

					adjust += theBody->GetVelocity();
				}
				if (adjust.y > 0.f && mVelocity.y < 0.f)
				{
					mVelocity.y = 0.f;
					mIsJumping = false;
				}

				if (adjust.y > 20.f)
					mCrushedFlag = true;

				myBody->GetOwner()->SetPosition(pos + adjust);
			}

			
			if (!mPlayer->GetLife()->GetInvincibleFlag())
				HitEnemy(myBody, theBody);
			
		}

		void PlayerState::Active::SetMode(PlayerMode::Mode* mode)
		{
			if (mMode != mode)
			{
				if (mMode)
					delete mMode;
				mMode = mode;
			}
		}

		void PlayerState::Active::HitEnemy(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "EnemyTriple" || name == "EnemyToge" || name == "EnemyFrog" || name == "EnemyBee" ||
				name == "EnemyCarrot" || name == "EnemyMaimai" || name == "Nail"||name=="EnemyMissile")
			{
				mPlayer->GetLife()->Damage();
			}
			else if (name == "EnemyTripleWeakness" || name == "EnemyFrogWeakness" || name == "EnemyBeeWeakness" || name == "EnemyStandLight" ||
				name == "EnemyCarrotWeakness" || name == "EnemyMaimaiWeakness" || name == "NailWeakness"||name=="EnemyMissileWeakness")
			{
				mVelocity.y = -5.f;
				//４フレームの間は飛べる
				mJumpFlag2 = 4;
			}
			else if (name == "Spore")
			{
				auto v = GameLib::Vector2::Normalize(theBody->GetVelocity()) * 0.5f;
				mVelocity += v;
			}
			else if (name == "EnemyDogu")
			{
				mVelocity *= 0.5f;
			}

		}

		PlayerState::Death::Death(Player* player)
			:StageState()
			,mPlayer(player)
			,mCnt(0)
		{
			player->GetAnim()->SetChannel(4);
			player->GetSubAnim()->SetChannel(1);

			player->BreakBody();
		}

		PlayerState::Death::~Death()
		{
		}

		StageState* Game::Stage::PlayerState::Death::Update()
		{
			float rot = mPlayer->GetRotation();
			rot += 0.2f;
			mPlayer->SetRotation(rot);

			GameLib::Vector2 pos = mPlayer->GetPosition();
			pos.y -= 4.f;
			mPlayer->SetPosition(pos);

			float scale = mPlayer->GetScale();
			scale *= 0.99f;
			mPlayer->SetScale(scale);

			if (mCnt > 180)
				mPlayer->GetStageScene()->PlayerIsDead();
			mCnt++;

			return this;
		}

		PlayerState::Goal::Goal(Player* player, const GameLib::Vector2& goalPos,const GameLib::Vector2& v)
			:StageState()
			, mPlayer(player)
			, mGoalPos(goalPos)
			,mVelocity(v)
			,mCnt(0)
			,mOnGround(false)
		{

		}
		PlayerState::Goal::~Goal()
		{

		}

		StageState* PlayerState::Goal::Update()
		{
			auto pos = mPlayer->GetPosition();


			if (mOnGround == true && mVelocity.x > 1.f)
				mPlayer->GetAnim()->SetChannel(1);
			else if (mOnGround == true)
				mPlayer->GetAnim()->SetChannel(0);
			else
				mPlayer->GetAnim()->SetChannel(3);

			mVelocity.x *= 0.95f;
			mVelocity.y += 0.7f;
			pos += mVelocity;

			if (mCnt == 120)
				new ScoreBoard(mPlayer->GetStageScene());
			
			mPlayer->SetPosition(pos);
			mCnt++;
			mOnGround = false;
			return this;
		}

		void PlayerState::Goal::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Ground")
			{
				auto adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, 0.f, 0.f);
				mPlayer->SetPosition(mPlayer->GetPosition() + adjust);
				if (adjust.y < 0.f)
				{
					mVelocity.y = 0.f;
					mOnGround = true;
				}
			}
		}

		void PlayerState::Goal::AdjustPosSub(const GameLib::Vector2& vec)
		{
			mGoalPos += vec;
		}


		namespace PlayerState
		{
			namespace PlayerMode
			{



				Mode::Mode(Player* player)
					:mPlayer(player)
					,mTranceformCnt(0)
				{
				}

				Mode::~Mode()
				{
				}

				void Mode::Update()
				{
					UpdateMode();
					mTranceformCnt++;
				}

				bool Mode::IsTranceformed()
				{
					return mTranceformCnt > 40;
				}

				Nomal::Nomal(Player* player)
					:Mode(player)
				{
					mPlayer->GetSubAnim()->SetChannel(0);
				}

				Nomal::~Nomal()
				{
				}

				void Nomal::UpdateMode()
				{
				}

				void Nomal::Action()
				{
				}

				Cock::Cock(Player* player)
					:Mode(player)
				{
					mPlayer->GetSubAnim()->SetChannel(5);
				}

				Cock::~Cock()
				{
				}

				void Cock::UpdateMode()
				{
					if (IsTranceformed())
						mPlayer->GetSubAnim()->SetChannel(4);
				}

				void Cock::Action()
				{
					auto pos = mPlayer->GetPosition();
					bool isRight = true;
					float ad = 30.f;
					if (mPlayer->GetAnim()->GetTextureFlip() == GameLib::TextureFlip::Horizontal)
					{
						ad *= -1.f;
						isRight = false;
					}
					pos.x += ad;
					new PlayerAction::Fork(mPlayer->GetStageScene(), pos, isRight);
				}


				Wizard::Wizard(Player* player)
					:Mode(player)
				{
					mPlayer->GetSubAnim()->SetChannel(3);
				}

				Wizard::~Wizard()
				{

				}

				void Wizard::UpdateMode()
				{
					if (IsTranceformed())
						mPlayer->GetSubAnim()->SetChannel(2);
				}

				void Wizard::Action()
				{
					new PlayerAction::Meteor(mPlayer->GetStageScene(), mPlayer->GetPosition().x);
				}

				Alien::Alien(Player* player)
					:Mode(player)
				{
					mPlayer->GetSubAnim()->SetChannel(7);
				}

				Alien::~Alien()
				{

				}

				void Alien::UpdateMode()
				{
					if (IsTranceformed())
						mPlayer->GetSubAnim()->SetChannel(6);
				}

				void Alien::Action()
				{
					if (PlayerAction::Beam::GetNum() < 3)
					{
						
						Vec2 adjust(100.f, 0.f);
						bool isRight = true;
						if (mPlayer->GetAnim()->GetTextureFlip() == GameLib::TextureFlip::Horizontal)
						{
							adjust.x *= -1.f;
							isRight = false;
						}
						new PlayerAction::Beam(mPlayer->GetStageScene(), mPlayer->GetPosition() + adjust, isRight);
					

					}
				}
			}
		}



	}




}

