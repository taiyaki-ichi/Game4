#pragma once
#include"SpriteComponent.hpp"
#include<string>

namespace GameLib
{
	class Font;
	class Vector2;
	class Vector3;
	
	enum class FontSize
	{
		Size_16,
		Size_32,
		Size_64,
		Size_96,
		Size_128
	};


	class TextComponent : public SpriteComponent
	{
	public:
		TextComponent(Actor* actor, const std::string& fliName, int drawOrder = 0, int updaOrder = 0);
		virtual ~TextComponent();

		void Draw() override;

		void SetText(const std::string& tex) { mText = tex; }
		void SetColor(const Vector3& color) { mColor = color; }
		void SetSize(const FontSize& size) { mSize = size; }
		void SetAlpha(float a) { mAlpha = a; }
		void SetAdjust(const Vector2& ad) { mAdjust = ad; }

		const std::string& GetText() const { return mText; }

	private:
		Font* mFont;
		std::string mText;
		Vector2 mAdjust;
		FontSize mSize;
		Vector3 mColor;
		float mAlpha;
	};


}