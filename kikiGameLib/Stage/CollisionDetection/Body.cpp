#include"Body.hpp"
#include"Stage/StageActor.hpp"
#include"Manager.hpp"
#include"Stage/StageScene.hpp"
#include"CollisionDetection.hpp"
#include"lib/include/Draw/SpriteComponent.hpp"
#include"lib/include/Math.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		bool Body::DrawFlag = true;
		GameLib::Vector2 Body::mScreenMoveAdjust(0.f, 0.f);

		Body::Body(StageActor* actor, const std::string& bodyName, int updateOrder)
			:SpriteComponent(actor, 10000, updateOrder)
			, mName(bodyName)
			, mWidth(0.f)
			, mHeight(0.f)
			, mAdjust()
			, mStageOwner(actor)
			, mColor(GameLib::Color::Black)
			,mVelocity(0.f,0.f)
		{
			mLinerObject = new LinerObject(this);
			mPrevPos = mOwner->GetPosition();
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

			Vec2 pos = GetOwner()->GetPosition();
			mPrevPos += Body::mScreenMoveAdjust;
			mVelocity = pos - mPrevPos;
			mPrevPos = pos;
		}


		void Body::Draw()
		{
			if (Body::DrawFlag)
			{
				using Vec2 = GameLib::Vector2;

				Vec2 point[4];
				Vec2 center = mOwner->GetPosition() + GetAdjust();
				GameLib::GetRotatedRect(point, center, GetWidth(), GetHeight(), mOwner->GetRotation());

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

		void Body::ResetVelocity()
		{
			mVelocity = Vec2(0.f, 0.f);
			mPrevPos = mOwner->GetPosition();
		}


		GameLib::Vector2 GetAdjustUnrotatedRectVec(Body* myBody, Body* theBody)
		{
			using Vec2 = GameLib::Vector2;

			Vec2 myPos = myBody->GetOwner()->GetPosition() + myBody->GetAdjust();
			Vec2 thePos = theBody->GetOwner()->GetPosition() + theBody->GetAdjust();

			float myWidth = myBody->GetWidth();
			float myHeight = myBody->GetHeight();

			float idealX = myWidth / 2.f + theBody->GetWidth() / 2.f;
			float idealY = myHeight / 2.f + theBody->GetHeight() / 2.f;

			//theに対するmyの相対的なVec
			Vec2 relativeVec = thePos - myPos;

			float adX = (relativeVec.x > 0.f) ? relativeVec.x - idealX : idealX + relativeVec.x;
			float adY = (relativeVec.y > 0.f) ? relativeVec.y - idealY : idealY + relativeVec.y;

			return Vec2(adX, adY);

		}

		GameLib::Vector2 GetAdjustUnrotatedRectVecEx(Body* myBody, Body* theBody, float myGravity, float myMaxSpeed)
		{
			using Vec2 = GameLib::Vector2;
			Vec2 adjust = GetAdjustUnrotatedRectVec(myBody, theBody);

			bool check = true;
			//引っかかりをなくすため、、、0.1は誤差の分

			if (GameLib::Math::Abs(adjust.y) <= GameLib::Math::Abs(myGravity) + 0.1f &&
				GameLib::Math::Abs(adjust.x) <= GameLib::Math::Abs(myMaxSpeed) + 0.1f)
			{
				adjust.x = 0.f;
				adjust.y = 0.f;
				check = false;
			}
			else if (GameLib::Math::Abs(adjust.y) <= GameLib::Math::Abs(myGravity)+0.1f)
			{
				adjust.x = 0.f;
				check = false;
			}
			else if (GameLib::Math::Abs(adjust.x) <= GameLib::Math::Abs(myMaxSpeed)+0.1f)
			{
				adjust.y = 0.f;
				check = false;
			}

			if (check)
			{
				if (GameLib::Math::Abs(adjust.x) < GameLib::Math::Abs(adjust.y))
				{
					adjust.y = 0.f;
				}
				else
				{
					adjust.x = 0.f;
				}
			}
			return adjust;
		}

}
}