#include"lib/include/Draw/LineComponent.hpp"
#include "..\..\include\Draw\LineComponent.hpp"

namespace GameLib
{
	LineComponent::LineComponent(Actor* actor, int drawOrder, int updateOrder)
		:SpriteComponent(actor,drawOrder,updateOrder)
		,mPoint1(0.f,0.f)
		,mPoint2(0.f,0.f)
		,mAlpha(255.f)
		,mColor(Color::Black)
	{
	}

	LineComponent::~LineComponent()
	{
	}

	void LineComponent::Draw()
	{
		DrawLine(mPoint1, mPoint2, mColor, mAlpha);
	}
}