#include"CollisionDetection.hpp"
#include"Body.hpp"
#include"include/Math.hpp"
#include"include/Actor.hpp"

namespace Game
{
	namespace Stage
	{
		bool CollisionDetection(Body* myBody, Body* theBody)
		{
			if (myBody == nullptr || theBody == nullptr)
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
			float sca = body->GetOwner()->GetScale();
			float rot = body->GetOwner()->GetRotation();

			Vec2 ad = Vec2::Rotation(body->GetAdjust(), rot);

			float w = body->GetWidth();
			float h = body->GetHeight();
			auto vec = Vec2(w / 2.f, h / 2.f);
			float l = GameLib::Math::Sqrt(w * w + h * h) / 2.f;
			float rot1 = GameLib::Math::Pi * h / (h + w);
			float rot2 = GameLib::Math::Pi - rot1;

			float pii = GameLib::Math::Pi;
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
				point[2] = Vec2::Rotation(vec, rot + pii) + ad + pos;
				point[3] = Vec2::Rotation(vec, rot - rot2) + ad + pos;
			}

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

			//SDLÇÃç¿ïWånÇÕê≥Ç™éûåvâÒÇË

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