#pragma once
#include"SpriteComponent.hpp"
#include<string>

namespace GameLib
{


	class TextureComponent : public SpriteComponent
	{
	public:
		TextureComponent(Actor* actor, int drawOrder = 0, int updateOrder = 0);
		TextureComponent(Actor* actor, const std::string& fileName,int drawOrder = 0, int updateOrder = 0);
		virtual ~TextureComponent();

		virtual void Draw() override;

		void SetTexture(Texture* tex) { mTexture = tex; }
		void SetTextureFlip(const TextureFlip& flip) { mTextureFilp = flip; }

	private:
		Texture* mTexture;
		TextureFlip mTextureFilp;
	};
}