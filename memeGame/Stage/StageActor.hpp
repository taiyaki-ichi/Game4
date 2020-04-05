#pragma once
#include"include/Actor.hpp"


namespace Game
{
	namespace Stage
	{
		class StageScene;
		class Body;

		class StageActor : public GameLib::Actor
		{
		public:
			StageActor(StageScene* scene, int updateOrder = 0);
			StageActor(StageScene* scene, const GameLib::Vector2& vec, int updateOrder = 0);
			virtual ~StageActor();

			void Update() override final;
			virtual void UpdateStageActor();

			//vec��Actor�̃|�W�V�������ړ�
			void AdjustPos(const GameLib::Vector2& vec);
			void AdjustPosSub(const GameLib::Vector2& vec);

			virtual void Hit(Body* myBody, Body* theBody);

			StageScene* GetStageScene() const { return mStageScene; }

			void SetRelativeMoveRate(float r) { mRelativeMoveRate = r; };

		private:
			StageScene* mStageScene;

			//���Έړ��̊���
			float  mRelativeMoveRate;

		};
	}
}