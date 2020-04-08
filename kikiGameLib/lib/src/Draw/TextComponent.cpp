#include"lib/include/Draw/TextComponent.hpp"
#include"lib/src/Windows/Graphics.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/Actor.hpp"

namespace GameLib
{



	TextComponent::TextComponent(Actor* actor, const std::string& fliName, int drawOrder, int updaOrder)
		:SpriteComponent(actor,drawOrder,updaOrder)
		,mText("")
		,mAdjust()
		,mSize(FontSize::Size_64)
		,mColor(Color::Black)
		,mAlpha(255.f)
	{
		mFont = Data::GetFont(fliName);
	}

	TextComponent::~TextComponent()
	{
	}

	void TextComponent::Draw()
	{
		if (mFont&&mText.size()>0)
		{
			Vector2 pos = mAdjust + mOwner->GetPosition();

			Graphics::DrawMyText(mFont, mText,
				pos,
				mSize,
				mColor,
				mAlpha
			);

		}
	}



}