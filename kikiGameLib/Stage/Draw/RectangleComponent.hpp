#pragma once
#include"lib/include/Draw/SpriteComponent.hpp"

namespace Game
{
	namespace Stage
	{

		class RectangleComponent : public GameLib::SpriteComponent
		{
		public:
			RectangleComponent(GameLib::Actor* actor, float w, float h,
				const GameLib::Vector3& color, float a = 255,
				float drawOrdeer=0,float updateOrder = 0);
			virtual ~RectangleComponent();

			void Draw() override;

			void SetColor(const GameLib::Vector3& color) { mColor = color; }
			void SetAdjust(const GameLib::Vector2& ad) { mAdjust = ad; }
			void SetWidth(float w) { mWidth = w; }
			void SetHeight(float h) { mHeight = h; }
			void SetWidthAndHeight(float w, float h) { mWidth = w; mHeight = h; }

		private:
			float mWidth;
			float mHeight;

			GameLib::Vector3 mColor;

			GameLib::Vector2 mAdjust;

			float mAlpha;
		};
	}
}