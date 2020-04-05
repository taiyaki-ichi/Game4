#include"include/Draw/TextureComponent.hpp"
#include"include/Data.hpp"
#include"include/Actor.hpp"
#include "..\..\include\Draw\TextureComponent.hpp"

#include<iostream>


namespace GameLib
{
	TextureComponent::TextureComponent(Actor* actor, int drawOrder, int updateOrder)
		:SpriteComponent(actor,drawOrder,updateOrder)
		,mTextureFilp(TextureFlip::None)
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
		
		Actor* owner = GetOwner();
		DrawTexture(mTexture,
			owner->GetPosition(),
			owner->GetRotation(),
			owner->GetScale(),
			mTextureFilp
		);
		
	}
}