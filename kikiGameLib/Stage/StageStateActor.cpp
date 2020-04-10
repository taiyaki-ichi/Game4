#pragma once
#include"StageStateActor.hpp"

namespace Game
{
	namespace Stage
	{

		StageStateActor::StageStateActor(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
			:StageActor(scene,pos,updateOrder)
			,mState(nullptr)
		{
		}

		StageStateActor::~StageStateActor()
		{
			if (mState)
				delete mState;
		}

		void StageStateActor::Input(const GameLib::InputState& state)
		{
			if (mState)
				mState->Input(state);
		}

		void StageStateActor::UpdateStageActor()
		{
			if (mState)
			{
				StageState* next = mState->Update();
				if (next != mState)
				{
					delete mState;
					mState = next;
				}
			}
		}

		void StageStateActor::Hit(Body* myBody, Body* theBody)
		{
			if (mState)
				mState->Hit(myBody, theBody);
		}

		void StageStateActor::AdjustPosSub(const GameLib::Vector2& vec)
		{
			if (mState)
				mState->AdjustPosSub(vec);
		}

		void StageStateActor::SetStageState(StageState* state)
		{
			if (mState)
			{
				if (mState != state)
				{
					delete mState;
					mState = state;
				}
			}
			else
				mState = state;
		}

	}
}