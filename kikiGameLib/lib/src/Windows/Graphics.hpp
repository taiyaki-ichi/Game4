#pragma once
#include<string>
#include<d3d9.h>
#include"lib/DirectX/d3dx9.h"
#include"lib/include/Math.hpp"
#include"lib/include/Draw/TextComponent.hpp"

namespace GameLib
{
	class Vector2;
	class Vector3;
	enum class TextureFlip;

	class GraphicsManager
	{
	public:
		GraphicsManager();
		~GraphicsManager();

		bool Init();

	};

	class Texture
	{
	public:
		Texture(LPDIRECT3DTEXTURE9 ptr,float w,float h);
		virtual ~Texture();

		LPDIRECT3DTEXTURE9 GetPtr() const { return mPtr; }
		float GetWidth() const { return mWidth; }
		float GetHeight() const { return mHeight; }

	private:
		LPDIRECT3DTEXTURE9 mPtr;
		float mWidth;
		float mHeight;
	};

	Texture* LoadTexture(const std::string& fileName);


	//SpriteComponent.cpp用
	namespace Graphics
	{
		void DrawTexture(Texture* texture, const Vector2& pos, float rot, float scale, const TextureFlip& filp);
		void DrawLine(const Vector2& point1, const Vector2& point2, const Vector3& color, float alpha);
		void DrawTriangle(const Vector2& point1, const Vector2& point2, const Vector2& point3, const Vector3& color,float alpha);
	}



	void DrawStart();
	void DrawEnd();

	struct CUSTOM_VERTEX
	{
		float x, y, z, rhw;
		// テクスチャ座標(横)
		float tu;
		// テクスチャ座標(縦)
		float tv;

	};

	struct CUSTOM_VERTEX2
	{
		float x, y, z, rhw;
	
		DWORD color;

	};
	
	enum class FontSize;

	class Font
	{
	public:
		static const int SizeNum = 5;

		Font(LPD3DXFONT font[SizeNum]);
		virtual ~Font();

		LPD3DXFONT GetPtr(int i) const { return mPtr[i]; }

	private:
		LPD3DXFONT mPtr[SizeNum];
	};

	Font* LoadFont(const std::string& fileName);

	namespace Graphics
	{
		void DrawMyText(Font* font, const std::string& text, const Vector2& center, const FontSize& size = FontSize::Size_32, const Vector3& color = Color::Black, float alpha = 255);
	}

}
