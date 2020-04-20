#pragma once
#include"Stage/StageStateActor.hpp"
#include<string>

namespace Game
{
	namespace StageSelect
	{
		class Scene;
		class StageIsland;
		class BackGround;

		class BackGroundManager
		{
		public:
			BackGroundManager();
			virtual ~BackGroundManager();

			void Add(BackGround* b);

			void Active();
			void Stay();

		private:
			std::vector<BackGround*> mBackGrounds;
		};

		class BackGround : public Stage::StageStateActor
		{
		public:
			BackGround(StageIsland* s, const GameLib::Vector2& pos = GameLib::Vector2(0.f, 0.f));
			virtual ~BackGround();

			virtual Stage::StageState* CreateActiveState()=0;
			virtual void SetMoveState() = 0;
			virtual void SetToActive()= 0;

			StageIsland* GetStageIsland() const { return mStageIsland; }

		private:
			StageIsland* mStageIsland;
		};

		namespace BackGroundState
		{
			enum class MoveDir
			{
				Up,
				Down,
				Left,
				Right,
			};

			constexpr float MOVESPEED = 8.f;

			class Move : public Stage::StageState
			{
			public:
				Move(BackGround* b, const MoveDir& d);
				virtual ~Move();

				virtual Stage::StageState* Update() override;

			private:
				BackGround* mBackGround;
				MoveDir mMoveDir;
			};

			class Stay : public Stage::StageState
			{
			public:
				Stay(BackGround* b);
				virtual ~Stay();

				virtual Stage::StageState* Update() override;
				virtual void AdjustPosSub(const GameLib::Vector2& vec) override;
			private:
				BackGround* mBackGround;

			};

			class ToActive : public Stage::StageState
			{
			public:
				ToActive(BackGround* b, const GameLib::Vector2& pre);
				virtual ~ToActive();

				virtual Stage::StageState* Update() override;
				
			private:
				BackGround* mBackGround;
				GameLib::Vector2 mPrevPos;

			};


			class Fall : public Stage::StageState
			{
			public:
				Fall(BackGround* b, const GameLib::Vector2& v, float rot);
				virtual ~Fall();

				virtual Stage::StageState* Update() override;

			private:
				BackGround* mBackGround;
				GameLib::Vector2 mVelocity;
				float mRot;
			};

			class RelativeStay : public Stage::StageState
			{
			public:
				RelativeStay() {};
				virtual ~RelativeStay() {};
			};
		}

		class Leaf : public BackGround
		{
		public:
			Leaf(StageIsland* s);
			virtual ~Leaf();

			virtual Stage::StageState* CreateActiveState() override;
			virtual void SetMoveState() override;
			virtual void SetToActive() override;
		};

		class Horizon130 : public BackGround
		{
		public:
			Horizon130(StageIsland* s);
			virtual ~Horizon130();

			virtual Stage::StageState* CreateActiveState() override;
			virtual void SetMoveState() override;
			virtual void SetToActive() override;
		};

		class Horizon180 : public BackGround
		{
		public:
			Horizon180(StageIsland* s);
			virtual ~Horizon180();

			virtual Stage::StageState* CreateActiveState() override;
			virtual void SetMoveState() override;
			virtual void SetToActive() override;
		};

		class Horizon230 : public BackGround
		{
		public:
			Horizon230(StageIsland* s);
			virtual ~Horizon230();

			virtual Stage::StageState* CreateActiveState() override;
			virtual void SetMoveState() override;
			virtual void SetToActive() override;
		};

		class FixedBackGround : public BackGround
		{
		public:
			FixedBackGround(StageIsland* s, const std::string& fileName, const GameLib::Vector2& pos, float scale, int drawOrder,float relative);
			virtual ~FixedBackGround();

			virtual Stage::StageState* CreateActiveState() override;
			virtual void SetMoveState() override;
			virtual void SetToActive() override;

		private:
			GameLib::Vector2 mPos;
		};

	}
}