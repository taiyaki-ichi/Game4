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

				if (pos.y > ActorUpdateScope::Bottom - 100.f ||
					pos.x > ActorUpdateScope::Right - 100.f ||
					pos.x < ActorUpdateScope::Left + 100.f)
					mStageActor->SetState(GameLib::Actor::State::Dead);

				return this;
			}

			DeathTimerState::DeathTimerState(StageActor* actor, int limit)
				:StageState()
				,mStageActor(actor)
				,mLimit(limit)
				,mCnt(0)
			{
			}

			DeathTimerState::~DeathTimerState()
			{
			}

			StageState* DeathTimerState::Update()
			{
				mCnt++;
				if (mCnt > mLimit)
					mStageActor->SetState(GameLib::Actor::State::Dead);
				return this;
			}

		}
	}
}