#pragma once
#include"lib/include/Actor.hpp"

namespace GameLib
{
	class TextureComponent;
	class TextComponent;
}

namespace StageEditor
{
	class EditingScene;

	class PlayerCounter : public GameLib::Actor
	{
	public:
		PlayerCounter(EditingScene* scene);
		virtual ~PlayerCounter();

		virtual void Update() override;

	private:
		GameLib::TextureComponent* mTexture;
		GameLib::TextComponent* mText;
	};

	class DiamondCounter : public GameLib::Actor
	{
	public:
		DiamondCounter(EditingScene* scene);
		virtual ~DiamondCounter();

		virtual void Update() override;
	private:
		GameLib::TextureComponent* mTexture;
		GameLib::TextComponent* mText;

	};

	class TearCounter : public GameLib::Actor
	{
	public:
		TearCounter(EditingScene* scene);
		virtual ~TearCounter();

		virtual void Update() override;
	private:
		GameLib::TextureComponent* mTexture;
		GameLib::TextComponent* mText;

	};
}