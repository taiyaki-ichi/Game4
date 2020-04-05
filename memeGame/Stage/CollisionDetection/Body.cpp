#include"Body.hpp"
#include"Stage/StageActor.hpp"
#include"Manager.hpp"
#include"Stage/StageScene.hpp"
#include"CollisionDetection.hpp"
#include"include/Draw/SpriteComponent.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		bool Body::DrawFlag = true;

		Body::Body(StageActor* actor, const std::string& bodyName, int updateOrder)
			:SpriteComponent(actor, 10000, updateOrder)
			, mName(bodyName)
			, mWidth(0.f)
			, mHeight(0.f)
			, mAdjust()
			, mStageOwner(actor)
			, mColor(GameLib::Color::Black)
		{
			mLinerObject = new LinerObject(this);
		}

		Body::Body(StageActor* actor, const std::string& bodyName, float width, float height, int updateOrder)
			:Body(actor, bodyName, updateOrder)
		{
			mWidth = width;
			mHeight = height;
		}

		Body::Body(StageActor* actor, const std::string& bodyName, float width, float height, const GameLib::Vector2& adust, int updateOrder)
			:Body(actor, bodyName, width, height, updateOrder)
		{
			mAdjust = adust;
		}

		Body::~Body()
		{
			if (mLinerObject->mCell)
				mLinerObject->RemoveFromList();
			delete mLinerObject;
		}

		void Body::Update()
		{
			mLinerObject->RemoveFromList();

			GetStageOwner()->GetStageScene()->GetTree()->Regist(mLinerObject);
		}


		void Body::Draw()
		{
			if (Body::DrawFlag)
			{
				using Vec2 = GameLib::Vector2;

				Vec2 point[4];
				GetPoints(point, this);

				for (int i = 0; i < 4; i++)
				{
					if (i < 3)
						GameLib::DrawLine(point[i], point[i + 1], mColor, 255);
					else
						GameLib::DrawLine(point[3], point[0], mColor, 255);
				}


			}
		}

		float Body::GetWidth() const
		{
			return mWidth * GetOwner()->GetScale();
		}

		float Body::GetHeight() const
		{
			return mHeight * GetOwner()->GetScale();
		}

		float Body::GetRotatedWidth()
		{
			float rot = GetOwner()->GetRotation();
			float pi = GameLib::Math::Pi;

			float s = GameLib::Math::Sin(rot);
			float c = GameLib::Math::Cos(rot);

			if (c < 0)
			{
				if (s >= 0)
					rot -= pi / 2.f;
				else
					rot -= pi;
			}
			else if (s < 0)
				rot -= pi * 3.f / 2.f;

			return GetWidth() * GameLib::Math::Cos(rot) + GetHeight() * GameLib::Math::Sin(rot);
		}

		float Body::GetRotatedHeight()
		{
			float rot = GetOwner()->GetRotation();
			float pi = GameLib::Math::Pi;

			float s = GameLib::Math::Sin(rot);
			float c = GameLib::Math::Cos(rot);

			if (c < 0)
			{
				if (s >= 0)
					rot -= pi / 2.f;
				else
					rot -= pi;
			}
			else if (s < 0)
				rot -= pi * 3.f / 2.f;

			return GetWidth() * GameLib::Math::Sin(rot) + GetHeight() * GameLib::Math::Cos(rot);
		}

		const  GameLib::Vector2& Body::GetAdjust() const
		{
			return mAdjust * GetOwner()->GetScale();
		}


	}
}