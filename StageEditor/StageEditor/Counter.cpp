#include"Counter.hpp"
#include"EditingActor.hpp"
#include"EditingScene.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"lib/include/Draw/TextureComponent.hpp"

namespace StageEditor
{
	PlayerCounter::PlayerCounter(EditingScene* scene)
		:GameLib::Actor(scene)
	{

		GameLib::Vector2 pos = GameLib::Vector2(16.f, 16.f);
		SetPosition(pos);
		SetScale(0.07f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/tama/icon.png",100);

		mText = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 100);
		mText->SetAdjust(GameLib::Vector2(600.f, 0.f));
		mText->SetSize(GameLib::FontSize::Size_32);
		mText->SetText("�~" + std::to_string(EditingPlayer::GetNum()));
	}
	PlayerCounter::~PlayerCounter()
	{
	}
	void PlayerCounter::Update()
	{
		mText->SetText("�~" + std::to_string(EditingPlayer::GetNum()));
	}


	DiamondCounter::DiamondCounter(EditingScene* scene)
		:GameLib::Actor(scene)
	{
		GameLib::Vector2 pos = GameLib::Vector2(16.f, 64.f);
		SetPosition(pos);
		SetScale(0.05f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Item/diamond02.png", 100);

		mText = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 100);
		mText->SetAdjust(GameLib::Vector2(840.f, 0.f));
		mText->SetSize(GameLib::FontSize::Size_32);
		mText->SetText("�~" + std::to_string(EditingDiamond::GetNum()));
	}

	DiamondCounter::~DiamondCounter()
	{
	}

	void DiamondCounter::Update()
	{
		mText->SetText("�~" + std::to_string(EditingDiamond::GetNum()));
	}

	TearCounter::TearCounter(EditingScene* scene)
		:GameLib::Actor(scene)
	{
		GameLib::Vector2 pos = GameLib::Vector2(16.f, 112.f);
		SetPosition(pos);
		SetScale(0.05f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Item/tear.png", 100);

		mText = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf", 100);
		mText->SetAdjust(GameLib::Vector2(840.f, 0.f));
		mText->SetSize(GameLib::FontSize::Size_32);
		mText->SetText("�~" + std::to_string(EditingTear::GetNum()));
	}

	TearCounter::~TearCounter()
	{
	}

	void TearCounter::Update()
	{
		mText->SetText("�~" + std::to_string(EditingTear::GetNum()));
	}

}