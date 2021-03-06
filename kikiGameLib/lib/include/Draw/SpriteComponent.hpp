#pragma once
#include"lib/include/Component.hpp"
#include"lib/include/Math.hpp"

namespace GameLib
{
	class Texture;
	class DrawMethod;

	enum class TextureFlip
	{
		None,			//なし
		Horizontal,		//水平方向に反転
		Vertical		//垂直方向に反転
	};
	
	//SpriteComponentのDraw内での使用
	void DrawTexture(Texture* texture, const Vector2& pos, float rot, float scale, const TextureFlip& filp);
	void DrawLine(const Vector2& point1, const Vector2& point2, const Vector3& color, float alpha);
	void DrawTriangle(const Vector2& point1, const Vector2& point2, const Vector2& point3, const Vector3& color, float alpha);

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(Actor* owner, int drawOrder = 0, int updateOrder = 0);
		virtual ~SpriteComponent();

		virtual void Draw() = 0;

		int GetDrawOrder() const { return mDrawOrder; }
		void SetDrawOrder(int d);

	private:

		//大きい方が手前
		int mDrawOrder;
	};

}
