#pragma once
#include"include/Scene.hpp"
#include"WindowData.hpp"
#include<vector>

namespace Game
{
	namespace Stage
	{
		class StageActor;
		class Player;
		class Liner4Tree;


		namespace CollisionDetectionScope
		{
			//��ʂ̃^�e���R�~�R�͈̔͂�tree�̗L���͈�
			constexpr float Left = WINDOW_WIDTH / 2.f - WINDOW_WIDTH * 3.f / 2.f;
			constexpr float Right = WINDOW_WIDTH / 2.f + WINDOW_WIDTH * 3.f / 2.f;
			constexpr float Top = WINDOW_HEIGHT / 2.f - WINDOW_HEIGHT * 3.f / 2.f;
			constexpr float Bottom = WINDOW_HEIGHT / 2.f - WINDOW_HEIGHT * 3.f / 2.f;
		}

		namespace ActorUpdateScope
		{
			//�����蔻����s�����̂̑傫���͗]�T��������300�~300�܂�
			constexpr float Left = CollisionDetectionScope::Left + 300.f;
			constexpr float Right = CollisionDetectionScope::Right - 300.f;
			constexpr float Top = CollisionDetectionScope::Top + 300.f;
			constexpr float Bottom = CollisionDetectionScope::Bottom - 300.f;
		}

		//��Ԃ𕪊�������x
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

		private:
			class Player* mPlayer;
			std::vector<StageActor*> mStageActors;

			Liner4Tree* mTree;
		};
	}
}
