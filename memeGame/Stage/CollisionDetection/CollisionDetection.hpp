#pragma once

namespace GameLib
{
	class Vector2;
}

namespace Game
{
	namespace Stage
	{
		class Body;

		bool CollisionDetection(Body* myBody, Body* theBody);

		void GetPoints(GameLib::Vector2 point[], Body* body);
		bool LineCollisionDetection(GameLib::Vector2 myPoint[], GameLib::Vector2 thePoint[]);
		bool CheckLineCross(const GameLib::Vector2& a1, const GameLib::Vector2& a2, const GameLib::Vector2& b1, const GameLib::Vector2& b2);
		bool CheckInclusion(const GameLib::Vector2& p, const GameLib::Vector2 point[]);
	}
}