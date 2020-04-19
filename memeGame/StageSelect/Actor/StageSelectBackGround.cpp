#include"StageSelectBackGround.hpp"
#include"WindowData.hpp"
#include"StageSelect/StageSelectScene.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/Player/Player.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"StageIsland.hpp"
#include"Stage/Draw/RectangleComponent.hpp"

namespace Game
{
	namespace StageSelect
	{
		BackGround::BackGround(StageIsland* s, const GameLib::Vector2& pos)
			:Stage::StageStateActor(s->GetStageScene(),pos)
			,mStageIsland(s)
		{
			s->AddBackGround(this);
		}
		BackGround::~BackGround()
		{
		}

		namespace BackGroundState
		{
			Move::Move(BackGround* b, const MoveDir& d)
				:StageState()
				,mMoveDir(d)
				,mBackGround(b)
			{

			}
			Move::~Move()
			{
			}
			Stage::StageState* Move::Update()
			{

				auto pos = mBackGround->GetPosition();

				float d = 100.f;

				if (mMoveDir == MoveDir::Right)
				{
					pos.x += MOVESPEED;
					if (pos.x > WINDOW_WIDTH + d)
						return new Stay(mBackGround);
				}
				else if (mMoveDir == MoveDir::Left)
				{
					pos.x -= MOVESPEED;
					if (pos.x < -d)
						return new Stay(mBackGround);
				}
				else if (mMoveDir == MoveDir::Down)
				{
					pos.y += MOVESPEED;
					if (pos.y > WINDOW_HEIGHT + d)
						return new Stay(mBackGround);

				}
				else if (mMoveDir == MoveDir::Up)
				{
					pos.y -= MOVESPEED;
					if (pos.y < -d)
						return new Stay(mBackGround);
				}

				mBackGround->SetPosition(pos);

				return this;
			}
			Stay::Stay(BackGround* b)
				:StageState()
				,mBackGround(b)
			{
			}
			Stay::~Stay()
			{

			}
			Stage::StageState* Stay::Update()
			{
				return this;
			}
			void Stay::AdjustPosSub(const GameLib::Vector2& vec)
			{
				mBackGround->SetPosition(mBackGround->GetPosition() - vec * mBackGround->GetRelativeMoveRate());
			}

			ToActive::ToActive(BackGround* b, const GameLib::Vector2& pre)
				:StageState()
				,mBackGround(b)
				,mPrevPos(pre)
			{
			}
			ToActive::~ToActive()
			{
			}
			Stage::StageState* ToActive::Update()
			{
				auto pos = mBackGround->GetPosition();
				auto vec = mPrevPos - pos;
				pos += GameLib::Vector2::Normalize(vec) * MOVESPEED;
				
				if ((mPrevPos - pos).Length() < MOVESPEED)
				{
					mBackGround->SetPosition(mPrevPos);
					return mBackGround->CreateActiveState();
				}
			
				mBackGround->SetPosition(pos);

				return this;
			}
			


			Fall::Fall(BackGround* s,const GameLib::Vector2& v,float rot)
				:Stage::StageState()
				,mBackGround(s)
				, mVelocity(v)
				, mRot(rot)
			{

			}

			Fall::~Fall()
			{

			}

			Stage::StageState* Fall::Update()
			{

				float d = 100.f;
				float w = WINDOW_WIDTH + d * 2.f;
				float h = WINDOW_HEIGHT + d * 2.f;

				auto pos = mBackGround->GetPosition();
				pos += mVelocity;

				if (pos.x < -d)
					pos.x += w;
				else if (WINDOW_WIDTH + d < pos.x)
					pos.x -= w;

				if (pos.y < -d)
					pos.y += h;
				else if (WINDOW_HEIGHT + d < pos.y)
					pos.y -= h;

				mBackGround->SetPosition(pos);

				mBackGround->SetRotation(mBackGround->GetRotation() + mRot);

				return this;
			}

		}

		Leaf::Leaf(StageIsland* s, const GameLib::Vector2& pos)
			:BackGround(s, pos)
		{
			SetScale(0.05f);
			new GameLib::TextureComponent(this, "../Assets/BackGround/leaf-160.png", -55);
			SetRelativeMoveRate(0.85f);

			SetStageState(new BackGroundState::Stay(this));
			int rr = std::rand() %100;
			SetRotation(GameLib::Math::TwoPi * rr / 100.f);

			int r = std::rand() % 4;
			if (r == 0)
				SetPosition(GameLib::Vector2(pos.x, -100.f));
			else if (r == 1)
				SetPosition(GameLib::Vector2(pos.x, WINDOW_HEIGHT+ 100.f));
			else if (r == 2)
				SetPosition(GameLib::Vector2(-100.f, pos.y));
			else
				SetPosition(GameLib::Vector2(WINDOW_WIDTH + 100.f, pos.y));
		}

		Leaf::~Leaf()
		{

		}

		Stage::StageState* Leaf::CreateActiveState()
		{
			return new BackGroundState::Fall(this,GameLib::Vector2(-2.f, 0.5f),0.05f);
		}

		void Leaf::SetMoveState()
		{
			int r = std::rand() % 4;
			if (r == 0)
				SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Left));
			else if(r==1)
				SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Right));
			else if (r == 2)
				SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Up));
			else 
				SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Down));


		}

		void Leaf::SetToActive()
		{
			int r1 = std::rand() % 1000;
			int r2 = std::rand() % 1000;

			float adX = (WINDOW_WIDTH + 100.f * 2.f) * r1 / 1000.f;
			float adY = (WINDOW_HEIGHT + 100.f * 2.f) * r2 / 1000.f;

			SetStageState(new BackGroundState::ToActive(this, GameLib::Vector2(-100.f + adX, -100.f + adY)));
		}

		BackGroundManager::BackGroundManager()
		{
		}

		BackGroundManager::~BackGroundManager()
		{
		}

		void BackGroundManager::Add(BackGround* b)
		{
			mBackGrounds.emplace_back(b);

		}

		void BackGroundManager::Active()
		{
			for (auto& b : mBackGrounds)
				b->SetToActive();
		}

		void BackGroundManager::Stay()
		{
			for (auto& b : mBackGrounds)
				b->SetMoveState();
		}

		Horizon130::Horizon130(StageIsland* s)
			:BackGround(s)
		{
			auto pos = GameLib::Vector2(s->GetPosition().x, WINDOW_HEIGHT + 100.f);
			SetPosition(pos);

			new Stage::RectangleComponent(this, WINDOW_WIDTH*1.5f, 50.f, GameLib::Vector3(130.f, 130.f, 130.f), 255, -50);
			SetStageState(new BackGroundState::Stay(this));

			SetRelativeMoveRate(0.f);
		}

		Horizon130::~Horizon130()
		{
		}

		Stage::StageState* Horizon130::CreateActiveState()
		{
			return new BackGroundState::Stay(this);
		}

		void Horizon130::SetMoveState()
		{
			SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Down));
		}

		void Horizon130::SetToActive()
		{
			float x = GetStageIsland()->GetPosition().x;
			SetPosition(GameLib::Vector2(x, GetPosition().y));
			SetStageState(new BackGroundState::ToActive(this, GameLib::Vector2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 170.f)));
		}

		Horizon180::Horizon180(StageIsland* s)
			:BackGround(s)
		{
			auto pos = GameLib::Vector2(s->GetPosition().x, WINDOW_HEIGHT + 100.f);
			SetPosition(pos);

			new Stage::RectangleComponent(this, WINDOW_WIDTH*1.5f, 50.f, GameLib::Vector3(180.f, 180.f, 180.f), 255, -60);
			SetStageState(new BackGroundState::Stay(this));

			SetRelativeMoveRate(0.f);
		}

		Horizon180::~Horizon180()
		{
		}

		Stage::StageState* Horizon180::CreateActiveState()
		{
			return new BackGroundState::Stay(this);
		}

		void Horizon180::SetMoveState()
		{
			SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Down));
		}

		void Horizon180::SetToActive()
		{
			float x = GetStageIsland()->GetPosition().x;
			SetPosition(GameLib::Vector2(x, GetPosition().y));
			SetStageState(new BackGroundState::ToActive(this, GameLib::Vector2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 220.f)));
		}

		Horizon230::Horizon230(StageIsland* s)
			:BackGround(s)
		{
			auto pos = GameLib::Vector2(s->GetPosition().x, WINDOW_HEIGHT + 100.f);
			SetPosition(pos);

			new Stage::RectangleComponent(this, WINDOW_WIDTH * 1.5f, 50.f, GameLib::Vector3(230.f, 230.f, 230.f), 255, -70);
			SetStageState(new BackGroundState::Stay(this));

			SetRelativeMoveRate(0.f);
		}

		Horizon230::~Horizon230()
		{
		}

		Stage::StageState* Horizon230::CreateActiveState()
		{
			return new BackGroundState::Stay(this);
		}

		void Horizon230::SetMoveState()
		{
			SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Down));
		}

		void Horizon230::SetToActive()
		{
			float x = GetStageIsland()->GetPosition().x;
			SetPosition(GameLib::Vector2(x, GetPosition().y));
			SetStageState(new BackGroundState::ToActive(this, GameLib::Vector2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 270.f)));
		}

		FixedBackGround::FixedBackGround(StageIsland* s, const std::string& fileName, const GameLib::Vector2& pos, float scale, int drawOrder, float relative)
			:BackGround(s)
			,mPos(pos)
		{
			SetScale(scale);
			
			new GameLib::TextureComponent(this, fileName, drawOrder);

			auto ppos = GameLib::Vector2(s->GetPosition().x, WINDOW_HEIGHT + 100.f);
			SetPosition(ppos);

			SetStageState(new BackGroundState::Stay(this));

			SetRelativeMoveRate(relative);



		}

		FixedBackGround::~FixedBackGround()
		{
		}

		Stage::StageState* FixedBackGround::CreateActiveState()
		{
			return new BackGroundState::RelativeStay();
		}

		void FixedBackGround::SetMoveState()
		{
			SetStageState(new BackGroundState::Move(this, BackGroundState::MoveDir::Down));
		}

		void FixedBackGround::SetToActive()
		{
			
			SetPosition(GameLib::Vector2(mPos.x, GetPosition().y));
			SetStageState(new BackGroundState::ToActive(this, mPos));
		}

}
}

