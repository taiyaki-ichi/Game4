#include"EditingActor.hpp"
#include"lib/include/InputState.hpp"
#include"EditingScene.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"lib/include/Draw/LineComponent.hpp"

#include<iostream>

namespace StageEditor
{
	using Vec2 = GameLib::Vector2;
	using Vec3 = GameLib::Vector3;

	EditingActor::EditingActor(EditingScene* scene,const Vec2& pos,const std::string& name,int dataNum)
		:Game::Stage::StageActor(scene)
		,mEditingScene(scene)
		,mName(name)
		,mDataNum(dataNum)
		,mClicked(false)
	{
		SetPosition(pos);
	}
	EditingActor::~EditingActor()
	{
		mEditingScene->RemoveEditingActor(this);
	}
	void EditingActor::Input(const GameLib::InputState& state)
	{
		GameLib::Vector2 pos = state.GetMousePos();
		mClicked = false;
		if (state.GetState(GameLib::MouseButton::Middle) == GameLib::ButtonState::Pressed && IsOk())
			mClicked == true;

		if (!IsOk())
			SetPosition(pos);

		if (state.GetState(GameLib::MouseButton::Middle) == GameLib::ButtonState::Pressed && !IsOk())
		{
			mDates.emplace_back(static_cast<double>(pos.x));
			mDates.emplace_back(static_cast<double>(pos.y));
		}
		
	}

	void EditingActor::UpdateStageActor()
	{

	}

	void EditingActor::AdjustPosSub(const Vec2& vec)
	{
		for (int i = 0; i < mDates.size(); i++)
		{
			if (i % 2 == 0) 
				mDates[i] += vec.x;
			else
				mDates[i] += vec.y;
			
		}
	}


	EditingPlayer::EditingPlayer(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Player",2)
		,mTexture(nullptr)
	{
		SetScale(0.1f);
		mTexture = new GameLib::TextureComponent(this, "Assets/tama/stay001.png");
		mBody = new Game::Stage::Body(this, "Player");
		mBody->SetWidthAndHeight(250.f, 500.f);
		mBody->SetAdjust(Vec2(0.f, 120.f));
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));

	}

	EditingPlayer::~EditingPlayer()
	{
	}


	EditingGround::EditingGround(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Ground",4)
	{
		mRect = new Game::Stage::RectangleComponent(this, 0.f, 0.f, Vec3(50.f, 50.f, 50.f));
		mBody = new Game::Stage::Body(this, "Ground");
		mBody->SetWidthAndHeight(0.f, 0.f);
		mBody->SetAdjust(Vec2(0.f, 0.f));
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));
	}

	EditingGround::~EditingGround()
	{
	}

	void EditingGround::UpdateStageActor()
	{
		int size = GetDatas().size();
		if (size == 2&&!IsOk())
		{
			Vec2 pos = GetPosition();
			Vec2 p = Vec2(GetDatas().at(0), GetDatas().at(1));

			float w = GameLib::Math::Abs(pos.x - p.x);
			float h = GameLib::Math::Abs(pos.y - p.y);

			Vec2 ad = (p - pos) / 2.f;

			mRect->SetAdjust(ad);
			mRect->SetWidthAndHeight(w, h);

			mBody->SetAdjust(ad);
			mBody->SetWidthAndHeight(w, h);
		}
		else if (size < 2&&!IsOk())
		{
			mRect->SetWidthAndHeight(0.f, 0.f);
		}
		else if (IsOk())
		{
			Vec2 p1 = Vec2(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2 = Vec2(GetDatas().at(2), GetDatas().at(3));

			SetPosition(p2);
			Vec2 ad = (p1 - p2) / 2.f;

			float w = GameLib::Math::Abs(p2.x - p1.x);
			float h = GameLib::Math::Abs(p2.y - p1.y);

			mRect->SetAdjust(ad);
			mRect->SetWidthAndHeight(w, h);

			mBody->SetAdjust(ad);
			mBody->SetWidthAndHeight(w, h);
		}
		
	}

	EditingTriple::EditingTriple(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Triple",2)
	{
		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/Triple-left-001.png");

		SetScale(0.1f);

		mBody = new Game::Stage::Body(this, "Trip");
		mBody->SetWidthAndHeight(350.f, 600.f);
		mBody->SetAdjust(Vec2(0.f, 60.f));
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));
	
		
	}

	EditingTriple::~EditingTriple()
	{
	}

	EditingToge::EditingToge(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Toge",2)
	{
		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/toge.png");
		SetScale(0.1f);

		mBody = new Game::Stage::Body(this, "Toge");
		mBody->SetWidthAndHeight(550.f, 550.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
		
	}

	EditingToge::~EditingToge()
	{
	}

	EditingFrog::EditingFrog(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Frog",4)
	{
		SetScale(0.08f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/frog001.png");

		mBody = new Game::Stage::Body(this, "Frog");
		mBody->SetWidthAndHeight(600.f, 650.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

		mLine = new GameLib::LineComponent(this, -1);
	}

	EditingFrog::~EditingFrog()
	{
	}

	void EditingFrog::UpdateStageActor()
	{
		int num = GetDatas().size();

		if (num == 0)
		{
			Vec2 p(0.f, 0.f);
			mLine->SetPoints(p, p);
		}
		else if (num == 2)
		{
			Vec2 p1(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2(GetDatas().at(0), GetEditingScene()->GetCursorPos().y);
			mLine->SetPoints(p1, p2);

			SetPosition(Vec2(GetDatas().at(0), GetDatas().at(1)));
		}
		else if (GetDatas().size() == 4)
		{
			Vec2 p1(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2(GetDatas().at(0), GetDatas().at(3));
			mLine->SetPoints(p1, p2);

			SetPosition(Vec2(GetDatas().at(0), GetDatas().at(1)));
		}
	}

}

