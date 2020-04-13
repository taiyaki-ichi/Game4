#pragma once
#include"lib/include/Draw/SpriteComponent.hpp"
#include<string>


namespace Game
{
	namespace Stage
	{
		class StageActor;
		class LinerObject;

		class Body : public GameLib::SpriteComponent
		{
		public:
			using Vec2 = GameLib::Vector2;

			Body(StageActor* actor, const std::string& bodyName, int updateOrder = 0);
			Body(StageActor* actor, const std::string& bodyName, float width, float height, int updateOrder = 0);
			Body(StageActor* actor, const std::string& bodyName, float width, float height, const Vec2& adust, int updateOrder = 0);
			virtual ~Body();

			void Update() override;
			//長方形の描写の際使用
			void Draw() override;

			static bool DrawFlag;
			static void SetDrawFlag(bool b) { DrawFlag = b; }

			//
			//以下、ゲッタヘッダ
			//

			void SetWidth(float w) { mWidth = w; }
			void SetHeight(float h) { mHeight = h; }
			void SetWidthAndHeight(float w, float h) { mWidth = w; mHeight = h; }
			float GetWidth() const;
			float GetHeight() const;

			float GetRotatedWidth();
			float GetRotatedHeight();

			void SetAdjust(const Vec2& adjust) { mAdjust = adjust; };
			const Vec2& GetAdjust() const;

			void SetColor(const GameLib::Vector3& color) { mColor = color; }

			StageActor* GetStageOwner() const { return mStageOwner; }

			const std::string& GetName() const { return mName; }
			void SetName(const std::string& name) { mName = name; }

			const Vec2& GetVelocity() const { return mVelocity; }
			void ResetVelocity();

			static void SetScreenMoveAdjust(const Vec2& vec) { mScreenMoveAdjust = vec; }

		private:
			float mWidth;
			float mHeight;

			//調整用のベクトル
			Vec2 mAdjust;

			//判別用の名前
			std::string mName;

			StageActor* mStageOwner;

			//長方形の色
			GameLib::Vector3 mColor;

			//４分木登録用
			LinerObject* mLinerObject;

			Vec2 mPrevPos;
			Vec2 mVelocity;
			static Vec2 mScreenMoveAdjust;
		};

		//回転していないBody同士のめり込みを補正するベクトルの取得
		GameLib::Vector2 GetAdjustUnrotatedRectVec(Body* myBody, Body* theBody);

		//theBodyが地面などの時の処理
		GameLib::Vector2 GetAdjustUnrotatedRectVecEx(Body* myBody, Body* theBody, float myGravity, float myMaxSpeed);

	}
}

