#pragma once
#include"lib/include/InputState.hpp"
#include"lib/include/Math.hpp"
#include<string>
#include<dinput.h>

namespace GameLib
{

	enum class Key;

	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();

		void Update();

		//a-z�̂ݓ��͉�
		//�L�[�̐^�U�̂�
		bool GetKeyValue(const Key& key) const;
		//�O�̃t���[���Ɣ�r���Ă̏��
		ButtonState GetKeyState(const Key& key) const;

	private:
		unsigned char mCurrState[256];
		unsigned char mPrevState[256];
	};

	class Mouse
	{
	public:

		Mouse();
		~Mouse();

		void Update();

		const Vector2& GetPosition() const { return mMousePos; }
		const Vector2& GetRelativePos() const { return mRelativeMousePos; }

		bool GetMouseButtonValue(MouseButton mouseButton) const;
		ButtonState GetMouseButtonState(MouseButton mouseButton) const;

	private:
		Vector2 mMousePos;
		Vector2 mRelativeMousePos;

		DIMOUSESTATE mCurrState;
		DIMOUSESTATE mPrevState;
	};


	class InputStateImpl : public InputState
	{
	public:
		InputStateImpl();
		virtual ~InputStateImpl();

		bool Init();

		void Update();

		bool GetValue(const Key& key) const override final;
		bool GetValue(const MouseButton& mouseButton) const override final;

		ButtonState GetState(const Key& key) const override final;
		ButtonState GetState(const MouseButton& mouseButton) const override final;

		//���݂̃}�E�X�̈ʒu
		const Vector2& GetMousePos() const override final;
		//�O��̃}�E�X�̈ʒu����̑��ΓI�Ȉʒu
		const Vector2& GetRelativeMousePos() const override final;

	private:
		Keyboard* mKeyboard;
		Mouse* mMouse;

	};

}