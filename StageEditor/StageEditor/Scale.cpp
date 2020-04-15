#include"Scale.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"EditingScene.hpp"

namespace StageEditor
{
	Scale::Scale(EditingScene* scene, bool isX, float num)
		:StageActor(scene)
		,mIsX(isX)
		,mNum(num)
	{
		mText = new GameLib::TextComponent(this, "Assets/Font/mplus.ttf");
		mText->SetSize(GameLib::FontSize::Size_16);
		mText->SetText(std::to_string(static_cast<int>(num)));

		if (mIsX)
		{
			GameLib::Vector2 pos(num, 8.f);
			SetPosition(pos);
		}
		else
		{
			GameLib::Vector2 pos(16.f, num);
			SetPosition(pos);
		}
	}
	Scale::~Scale()
	{
	}
	void Scale::UpdateStageActor()
	{
		auto pos = GetPosition();
		float line;
		float point;
		if (mIsX)
		{
			line = WINDOW_WIDTH;
			point = pos.x;
		}
		else
		{
			line = WINDOW_HEIGHT;
			point = pos.y;

		}

		if (point > line)
		{
			point -= line;
			mNum -= line;
			mText->SetText(std::to_string(static_cast<int>(mNum)));
		}
		else if (point <= 0.f)
		{
			point += line;
			mNum += line;
			mText->SetText(std::to_string(static_cast<int>(mNum)));
		}

		if (mIsX)
			SetPosition(GameLib::Vector2(point, pos.y));
		else
			SetPosition(GameLib::Vector2(pos.x, point));
	
	}
	void Scale::AdjustPosSub(const GameLib::Vector2& vec)
	{

		if (mIsX)
		{
			GameLib::Vector2 adjust(0.f, -vec.y);
			SetPosition(GetPosition() + adjust);
		}
		else
		{
			GameLib::Vector2 adjust(-vec.x, 0.f);
			SetPosition(GetPosition() + adjust);
		}
	}
}