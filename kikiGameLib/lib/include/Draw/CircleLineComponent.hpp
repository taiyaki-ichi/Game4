#pragma once
#include"SpriteComponent.hpp"

namespace GameLib
{
	class CircleLineComponent : public SpriteComponent
	{
	public:
		CircleLineComponent(Actor* actor, int drawOrder = 0, int updateOrder = 0);
		virtual ~CircleLineComponent();

		virtual void Draw() override;

		void SetRadius(float r) { mRadius = r; }
		void SetAdjust(const Vector2& ad) { mAdjust = ad; }

	private:
		float mAlpha;
		Vector3 mColor;

		float mRadius;
		Vector2 mAdjust;
	};

}