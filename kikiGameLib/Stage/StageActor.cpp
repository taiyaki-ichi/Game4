#include"StageActor.hpp"
#include"StageScene.hpp"


namespace Game
{
	namespace Stage
	{

		StageActor::StageActor(StageScene* scene, int updateOrder)
			:GameLib::Actor(scene, updateOrder)
			, mRelativeMoveRate(1.f)
			, mStageScene(scene)
		{
			scene->AddStageActor(this);
		}
		StageActor::StageActor(StageScene* scene, const GameLib::Vector2& vec, int updateOrder)
			:StageActor(scene, updateOrder)
		{
			SetPosition(vec);
		}

		StageActor::~StageActor()
		{
			mStageScene->RemoveStageActor(this);
		}

		void StageActor::Update()
		{
			auto pos = GetPosition();
			if (ActorUpdateScope::Left < pos.x && pos.x < ActorUpdateScope::Right &&
				ActorUpdateScope::Top < pos.y && pos.y < ActorUpdateScope::Bottom)
			{
				UpdateStageActor();
			}
		}

		void StageActor::UpdateStageActor()
		{
		}

		void StageActor::AdjustPos(const GameLib::Vector2& vec)
		{
			auto pos = GetPosition();
			pos += vec * mRelativeMoveRate;
			SetPosition(pos);

			AdjustPosSub(vec);
		}

		void StageActor::AdjustPosSub(const GameLib::Vector2& vec)
		{
		}

		void StageActor::Hit(Body* myBody, Body* theBody)
		{
		}
	}
}