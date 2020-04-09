#include"CollisionDetection.hpp"
#include"Body.hpp"
#include"lib/include/Math.hpp"
#include"lib/include/Actor.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		bool CollisionDetection(Body* myBody, Body* theBody)
		{
			if (myBody == nullptr || theBody == nullptr)
				return false;
			if (myBody->GetWidth() <= 0.f || myBody->GetHeight() <= 0.f ||
				theBody->GetWidth() <= 0.f || theBody->GetHeight() <= 0.f)
				return false;

			using Vec2 = GameLib::Vector2;

			Vec2 myPoints[4];
			GetPoints(myPoints, myBody);

			Vec2 thePoints[4];
			GetPoints(thePoints, theBody);

			for (int i = 0; i < 4; i++)
				if (CheckInclusion(myPoints[i], thePoints))
					return true;
			for (int i = 0; i < 4; i++)
				if (CheckInclusion(thePoints[i], myPoints))
					return true;

			if (LineCollisionDetection(myPoints, thePoints))
				return true;

			return false;


		}

		void GetPoints(GameLib::Vector2 point[], Body* body)
		{
			using Vec2 = GameLib::Vector2;

			auto pos = body->GetOwner()->GetPosition();
			float rot = body->GetOwner()->GetRotation();

			Vec2 ad = Vec2::Rotation(body->GetAdjust(), rot);
			
			float wi = body->GetWidth()/2.f;
			float hei = body->GetHeight()/2.f;
			point[0] = Vec2(wi, hei);
			point[1] = Vec2(wi, -hei);
			point[2] = Vec2(-wi, -hei);
			point[3] = Vec2(-wi, hei);
			GameLib::GetRotatedRect(point, Vec2(0.f, 0.f), rot);
			for (int i = 0; i < 4; i++)
				point[i] += ad + pos;

		}

		bool LineCollisionDetection(GameLib::Vector2 myPoint[], GameLib::Vector2 thePoint[])
		{
			bool flag = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i == 3 && j == 3)
					{
						flag = CheckLineCross(myPoint[3], myPoint[0], thePoint[3], thePoint[0]);
					}
					else if (i == 3)
					{
						flag = CheckLineCross(myPoint[3], myPoint[0], thePoint[j], thePoint[j + 1]);
					}
					else if (j == 3)
					{
						flag = CheckLineCross(myPoint[i], myPoint[i + 1], thePoint[3], thePoint[0]);
					}
					else
					{
						flag = CheckLineCross(myPoint[i], myPoint[i + 1], thePoint[j], thePoint[j + 1]);
					}

					if (flag == true)
						return true;
				}
			}

			return false;

		}


		bool CheckLineCross(const GameLib::Vector2& a1, const GameLib::Vector2& a2, const GameLib::Vector2& b1, const GameLib::Vector2& b2)
		{
			using Vec2 = GameLib::Vector2;
			if (Vec2::Cross(a2 - a1, b1 - a2) * Vec2::Cross(a2 - a1, b2 - a2) < 0 &&
				Vec2::Cross(b2 - b1, a1 - b2) * Vec2::Cross(b2 - b1, a2 - b2) < 0)
				return true;
			else
				return false;
		}

		bool CheckInclusion(const GameLib::Vector2& p, const GameLib::Vector2 point[])
		{

			using Vec2 = GameLib::Vector2;
			float right, left;

			//SDL‚ÌÀ•WŒn‚Í³‚ªŽžŒv‰ñ‚è

			if (Vec2::Cross(point[0] - point[3], p - point[0]) > 0)
				return false;
			if (Vec2::Cross(point[1] - point[0], p - point[1]) > 0)
				return false;
			if (Vec2::Cross(point[2] - point[1], p - point[2]) > 0)
				return false;
			if (Vec2::Cross(point[3] - point[2], p - point[3]) > 0)
				return false;

			return true;

		}


	}
}