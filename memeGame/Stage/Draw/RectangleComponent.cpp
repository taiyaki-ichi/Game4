#include"RectangleComponent.hpp"
#include"include/Actor.hpp"
#include"include/Math.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{

		RectangleComponent::RectangleComponent(GameLib::Actor* actor, float w, float h, const GameLib::Vector3& color, float a, float drawOrdeer, float updateOrder)
			:GameLib::SpriteComponent(actor,drawOrdeer,updateOrder)
			,mWidth(w)
			,mHeight(h)
			,mColor(color)
			,mAdjust()
			,mAlpha(a)
		{
		}

		RectangleComponent::~RectangleComponent()
		{
		}

		void RectangleComponent::Draw()
		{
			using Vec2 = GameLib::Vector2;
			Vec2 pos = mOwner->GetPosition();
			float rot = mOwner->GetRotation();

			Vec2 point[4];
			GameLib::GetRotatedRect(point, pos, mWidth, mHeight, rot);

			GameLib::DrawTriangle(point[1], point[0], point[3], mColor, mAlpha);
			GameLib::DrawTriangle(point[2], point[1], point[3], mColor, mAlpha);

		}
	}
}