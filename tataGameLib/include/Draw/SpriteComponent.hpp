#pragma once
#include"include/Component.hpp"
#include"include/Math.hpp"

namespace GameLib
{
	class Texture;
	class DrawMethod;

	enum class TextureFlip
	{
		None,			//‚È‚µ
		Horizontal,		//…•½•ûŒü‚É”½“]
		Vertical		//‚’¼•ûŒü‚É”½“]
	};
	
	//SpriteComponent‚ÌDraw“à‚Å‚Ìg—p
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

		//‘å‚«‚¢•û‚ªè‘O
		int mDrawOrder;
	};

}
