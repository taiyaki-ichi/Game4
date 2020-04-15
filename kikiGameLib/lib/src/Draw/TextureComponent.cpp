#include"lib/include/Draw/TextureComponent.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/Actor.hpp"

#include<iostream>
#include "..\..\include\Draw\TextureComponent.hpp"


namespace GameLib
{
	TextureComponent::TextureComponent(Actor* actor, int drawOrder, int updateOrder)
		:SpriteComponent(actor,drawOrder,updateOrder)
		,mTextureFilp(TextureFlip::None)
		,mAdjust(0.f,0.f)
	{
	}
	TextureComponent::TextureComponent(Actor* actor, const std::string& fileName, int drawOrder, int updateOrder)
		:TextureComponent(actor,drawOrder,updateOrder)
	{
		mTexture = Data::GetTexture(fileName);
	}
	TextureComponent::~TextureComponent()
	{
	}
	void TextureComponent::Draw()
	{
	
		Vector2 pos = mOwner->GetPosition() + mAdjust * GetOwner()->GetScale();
		DrawTexture(mTexture,
			pos,
			mOwner->GetRotation(),
			mOwner->GetScale(),
			mTextureFilp
		);
		
	}
	void TextureComponent::SetAdjust(const Vector2& ad)
	{
		mAdjust = ad;
	}
}