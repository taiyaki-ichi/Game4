#pragma once
#include"SpriteComponent.hpp"

namespace GameLib
{
	class LineComponent : public SpriteComponent
	{
	public:
		LineComponent(Actor* actor, int drawOrder = 0, int updateOrder=0);
		virtual ~LineComponent();

		virtual void Draw() override;

		void SetPoints(const Vector2& p1, const Vector2& p2) { mPoint1 = p1; mPoint2 = p2; }

		void SetAlpha(float a) { mAlpha = a; }
		void SetColor(const Vector3& color) { mColor = color; }

	private:
		Vector2 mPoint1;
		Vector2 mPoint2;

		float mAlpha;
		Vector3 mColor;
	};
}