#include"EditingActor.hpp"
#include"lib/include/InputState.hpp"
#include"EditingScene.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Draw/RectangleComponent.hpp"

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

			if (IsOk())
			{
				if (mEditingScene->AddEditingActor(this))
					mEditingScene->SetCurrEditingActor(nullptr);
			}
		}
		
	}

	void EditingActor::UpdateStageActor()
	{

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
		mBody = new Game::Stage::Body(this, "Player");
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
		if (size == 2 && !IsOk())
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
		else if (size < 2 && !IsOk())
		{
			mRect->SetWidthAndHeight(0.f, 0.f);
		}
		
	}

}

