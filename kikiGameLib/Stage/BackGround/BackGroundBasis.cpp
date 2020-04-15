#include"BackGroundBasis.hpp"
#include"WindowData.hpp"
#include"Stage/Draw/RectangleComponent.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		using Vec2 = GameLib::Vector2;

		BackGroundBasis::BackGroundBasis(StageScene* scene, int updateOrder)
			:StageActor(scene,Vec2(WINDOW_WIDTH/2.f,750.f),updateOrder)
			,mMoveSum(0.f,0.f)
		{
			new RectangleComponent(this, 900.f, 700.f, GameLib::Vector3(130.f, 130.f, 130.f), 255.f, -50);

			SetRelativeMoveRate(0.8f);
		}

		BackGroundBasis::~BackGroundBasis()
		{
		}

		void BackGroundBasis::AdjustPosSub(const GameLib::Vector2& vec)
		{
			float rate = GetRelativeMoveRate();
			mMoveSum += vec;
			Vec2 adjust(-vec.x*rate, 0.f);
			if (mMoveSum.y < -500.f)
				adjust.y = -vec.y * rate;
			SetPosition(GetPosition() + adjust);

		}

		Horaizon180::Horaizon180(StageScene* scene, int updateOrder)
			:StageActor(scene, Vec2(WINDOW_WIDTH / 2.f, 650.f),updateOrder)
		{
			new RectangleComponent(this, 900.f, 700.f, GameLib::Vector3(180.f, 180.f, 180.f), 255.f, -60);

			SetRelativeMoveRate(0.6f);
		}

		Horaizon180::~Horaizon180()
		{
		}

		void Horaizon180::AdjustPosSub(const GameLib::Vector2& vec)
		{
			Vec2 adjust(-vec.x * GetRelativeMoveRate(), 0.f);
			SetPosition(GetPosition() + adjust);
		}

		Horaizon230::Horaizon230(StageScene* scene, int updateOrder)
			:StageActor(scene,Vec2(WINDOW_WIDTH/2.f,550.f),updateOrder)
		{
			new RectangleComponent(this, 900.f, 700.f, GameLib::Vector3(230.f, 230.f, 230.f), 255.f, -70);

			SetRelativeMoveRate(0.4f);
		}

		Horaizon230::~Horaizon230()
		{
		}

		void Horaizon230::AdjustPosSub(const GameLib::Vector2& vec)
		{
			Vec2 adjust(-vec.x * GetRelativeMoveRate(), 0.f);
			SetPosition(GetPosition() + adjust);
		}

	}
}