#pragma once
#include"Stage/StageActor.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Item
		{

			class TransformItem : public StageActor
			{
			public:
				TransformItem(StageScene* scene, const GameLib::Vector2& pos,int updateOrder = 0);
				virtual ~TransformItem();

				virtual void UpdateStageActor() override;
			

			private:
				int mCnt;
			};

			class Cock : public TransformItem
			{
			public:
				Cock(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Cock();
			};

			class Wizard : public TransformItem
			{
			public:
				Wizard(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Wizard();
			};

			class Alien : public TransformItem
			{
			public:
				Alien(StageScene* scene, const GameLib::Vector2& pos, int updateOrder = 0);
				virtual ~Alien();
			};

		}
		
	}
}