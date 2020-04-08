#pragma once
#include<string>

namespace GameLib
{

	class Vector2;

	enum class ButtonState
	{
		None,
		Pressed,
		Released,
		Held,
	};

	enum class Key
	{
		Q = 0x10,
		W = 0x11,
		E = 0x12,
		R = 0x13,
		T = 0x14,
		Y = 0x15,
		U = 0x16,
		I = 0x17,
		O = 0x18,
		P = 0x19,
		A = 0x1E,
		S = 0x1F,
		D = 0x20,
		F = 0x21,
		G = 0x22,
		H = 0x23,
		J = 0x24,
		K = 0x25,
		L = 0x26,
		Z = 0x2C,
		X = 0x2D,
		C = 0x2E,
		V = 0x2F,
		B = 0x30,
		N = 0x31,
		M = 0x32,

		no1 = 0x02,
		no2 = 0x03,
		no3 = 0x04,
		no4 = 0x05,
		no5 = 0x06,
		no6 = 0x07,
		no7 = 0x08,
		no8 = 0x09,
		no9 = 0x0A,
		no0 = 0x0B,

		Esc=0x01,
		BackSpace=0x0E,
		Tab=0x0F,
		Enter=0x1C,
		LeftCtrl=0x1D,
		LeftShift=0x2A,
		RightShift=0x36,
		RightCtrl = 0x9D,
		Space=0x39,

		Up=0xC8,
		Left=0xCB,
		Right=0xCD,
		Down=0xD0,

	};

	enum class MouseButton
	{
		Left = 2,
		Middle = 0,
		Right = 1,
	};


	class InputState
	{
	protected:
		InputState() = default;
	public:
		virtual ~InputState() = default;

		virtual bool GetValue(const Key& key) const = 0;
		virtual bool GetValue(const MouseButton& mouseButton) const = 0;

		virtual ButtonState GetState(const Key& key) const = 0;
		virtual ButtonState GetState(const MouseButton& mouseButton) const = 0;

		//現在のマウスの位置
		virtual const Vector2& GetMousePos() const = 0;
		//前回のマウスの位置からの相対的な位置
		virtual const Vector2& GetRelativeMousePos() const = 0;

	};
}