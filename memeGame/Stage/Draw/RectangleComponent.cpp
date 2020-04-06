#include"RectangleComponent.hpp"
#include"include/Actor.hpp"

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
			float scale = mOwner->GetScale();

			float w = mWidth * scale;
			float h = mHeight * scale;

			Vec2 vec = Vec2(w / 2.f, h / 2.f);

			Vec2 ad = Vec2::Rotation(mAdjust, rot);

			float rot1 = GameLib::Math::Pi * h / (h + w);
			float rot2 = GameLib::Math::Pi - rot1;

			Vec2 point[4];
			if (rot == 0.f)
			{
				//rotationÇÕåÎç∑Ç™ëÂÇ´Ç¢ÇΩÇﬂ
				point[0] = vec + ad + pos;
				vec.y *= -1.f;
				point[1] = vec + ad + pos;
				vec.x *= -1.f;
				point[2] = vec + ad + pos;
				vec.y *= -1.f;
				point[3] = vec + ad + pos;
			}
			else
			{
				point[0] = Vec2::Rotation(vec, rot) + ad + pos;
				point[1] = Vec2::Rotation(vec, rot + rot1) + ad + pos;
				point[2] = Vec2::Rotation(vec, rot + GameLib::Math::Pi) + ad + pos;
				point[3] = Vec2::Rotation(vec, rot - rot2) + ad + pos;
			}
		
			GameLib::DrawTriangle(point[1], point[0], point[3], mColor, mAlpha);
			GameLib::DrawTriangle(point[2], point[1], point[3], mColor, mAlpha);

		}
	}
}