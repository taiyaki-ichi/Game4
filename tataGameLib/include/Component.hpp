#pragma once

namespace GameLib
{
	class Actor;
	class InputState;

	class Component
	{
	public:
		Component(Actor* actor, int updateOrder = 0);
		virtual ~Component();

		virtual void Input(const InputState& state);
		virtual void Update();

		//
		//以下、ゲッターセッター
		//

		class Actor* GetOwner() const { return mOwner; }

		int GetUpdateOrder() const { return mUpdateOrder; }


	protected:
		//Componentを所有するActor
		Actor* mOwner;

	private:

		//Componentの更新順序
		int mUpdateOrder;


	};
}