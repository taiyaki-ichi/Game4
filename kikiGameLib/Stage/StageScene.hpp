#pragma once
#include"lib/include/Scene.hpp"
#include"WindowData.hpp"
#include<vector>
#include<string>

namespace GameLib
{
	class Vector2;
}

namespace Game
{
	namespace Stage
	{
		class StageActor;
		class Player;
		class Liner4Tree;


		namespace CollisionDetectionScope
		{
			//画面のタテヨコ×３の範囲がtreeの有効範囲
			constexpr float Left = WINDOW_WIDTH / 2.f - WINDOW_WIDTH * 3.f / 2.f;
			constexpr float Right = WINDOW_WIDTH / 2.f + WINDOW_WIDTH * 3.f / 2.f;
			constexpr float Top = WINDOW_HEIGHT / 2.f - WINDOW_HEIGHT * 3.f / 2.f;
			constexpr float Bottom = WINDOW_HEIGHT / 2.f + WINDOW_HEIGHT * 3.f / 2.f;
		}

		namespace ActorUpdateScope
		{
			//当たり判定を行う物体の大きさは余裕をもって300×300まで
			constexpr float Left = CollisionDetectionScope::Left + 300.f;
			constexpr float Right = CollisionDetectionScope::Right - 300.f;
			constexpr float Top = CollisionDetectionScope::Top + 300.f;
			constexpr float Bottom = CollisionDetectionScope::Bottom - 300.f;
		}

		//空間を分割する程度
		constexpr unsigned int TREELEVEL = 6;

		class StageScene : public GameLib::Scene
		{
		public:
			StageScene();
			virtual ~StageScene();

			GameLib::Scene* Update() override final;
			virtual GameLib::Scene* UpdateStageScene();

			void AddStageActor(StageActor* actor);
			void RemoveStageActor(StageActor* actor);

			Liner4Tree* GetTree() const { return mTree; }
			void SetPlayer(Player* p) { mPlayer = p; }



		private:
			class Player* mPlayer;
			std::vector<StageActor*> mStageActors;

			Liner4Tree* mTree;

			float mStageLeft;
			float mStageRight;

		protected:
			//Stageの幅やPlayerの位置によってスクリーンを動かす
			void AdjustScreen();
			//vだけ動かす
			void MoveScreen(const GameLib::Vector2& vec);
		};

		bool LoadStageData(StageScene* scene, const std::string& fileName);

	}
}

