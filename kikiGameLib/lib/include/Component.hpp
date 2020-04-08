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
		//�ȉ��A�Q�b�^�[�Z�b�^�[
		//

		class Actor* GetOwner() const { return mOwner; }

		int GetUpdateOrder() const { return mUpdateOrder; }


	protected:
		//Component�����L����Actor
		Actor* mOwner;

	private:

		//Component�̍X�V����
		int mUpdateOrder;


	};
}