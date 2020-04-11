#include"lib/include/Draw/CircleLineComponent.hpp"
#include "..\..\include\Draw\CircleLineComponent.hpp"
#include"lib/include/Actor.hpp"

namespace GameLib
{

	CircleLineComponent::CircleLineComponent(Actor* actor, int drawOrder, int updateOrder)
		:SpriteComponent(actor,drawOrder,updateOrder)
		,mAlpha(255.f)
		,mColor(Color::Black)
		,mAdjust(0.f,0.f)
		,mRadius(0.f)
	{
	}

	CircleLineComponent::~CircleLineComponent()
	{
	}

	void CircleLineComponent::Draw()
	{
		if (mRadius > 0.f)
		{

			int num = static_cast<int>(mRadius)/4;
			Vector2 center = mOwner->GetPosition() + mAdjust;
			float r = mRadius * mOwner->GetScale();
			Vector2 vec = Vector2(mRadius, 0.f);

			Vector2 p1 = center + vec;
			Vector2 p2;
			for (int i = 0; i < num+1; i++)
			{
				p2 = Vector2::Rotation(vec, Math::TwoPi / num * i) + center;
				DrawLine(p1, p2, mColor, mAlpha);
				p1 = p2;
			}
		}
	}

}