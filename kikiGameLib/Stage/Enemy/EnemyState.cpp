#include"EnemyState.hpp"
#include"lib/include/Math.hpp"
#include"Stage/StageActor.hpp"
#include"Stage/StageScene.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{

			Fall::Fall(StageActor* actor)
				:mStageActor(actor)
			{
			}

			Fall::~Fall()
			{
			}

			StageState* Fall::Update()
			{
				GameLib::Vector2 pos = mStageActor->GetPosition();
				pos.y += 3.f;
				mStageActor->SetPosition(pos);

				float rot = mStageActor->GetRotation();
				rot += 0.1f;
				mStageActor->SetRotation(rot);

				if (pos.y > ActorUpdateScope::Bottom - 100.f)
					mStageActor->SetState(GameLib::Actor::State::Dead);

				return this;
			}

		}
	}
}