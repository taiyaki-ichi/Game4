#pragma once
#include"include/Draw/SpriteComponent.hpp"
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
		};


	}
}

