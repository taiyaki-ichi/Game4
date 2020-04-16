#include"EditingActor.hpp"
#include"lib/include/InputState.hpp"
#include"EditingScene.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"lib/include/Draw/LineComponent.hpp"
#include"lib/include/Draw/CircleLineComponent.hpp"

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

	EditingStraightBee::EditingStraightBee(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"StraightBee",4)
	{
		SetScale(0.08f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/bee001.png");

		mBody = new Game::Stage::Body(this, "StraightBee");
		mBody->SetWidthAndHeight(500.f, 400.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

		mLine = new GameLib::LineComponent(this, -1);
	}

	EditingStraightBee::~EditingStraightBee()
	{
	}

	void EditingStraightBee::UpdateStageActor()
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
			Vec2 p2(GetEditingScene()->GetCursorPos().x, GetEditingScene()->GetCursorPos().y);
			mLine->SetPoints(p1, p2);

			Vec2 dirVec = p2 - p1;
			float rot = GameLib::Math::Atan2(dirVec.x, dirVec.y);
			SetRotation(rot + GameLib::Math::Pi / 2.f);

			SetPosition(Vec2(GetDatas().at(0), GetDatas().at(1)));
		}
		else if (GetDatas().size() == 4)
		{
			Vec2 p1(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2(GetDatas().at(2), GetDatas().at(3));
			mLine->SetPoints(p1, p2);

			Vec2 dirVec = p2 - p1;
			float rot = GameLib::Math::Atan2(dirVec.x, dirVec.y);
			SetRotation(rot + GameLib::Math::Pi / 2.f);

			SetPosition(Vec2(GetDatas().at(0), GetDatas().at(1)));
		}
	}

	EditingCircleBee::EditingCircleBee(EditingScene* scene, const Vec2& pos)
		: EditingActor(scene, pos, "CircleBee", 6)
	{
		SetScale(0.08f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/bee001.png");

		mBody = new Game::Stage::Body(this, "CircleBee");
		mBody->SetWidthAndHeight(500.f, 400.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

		mLine1 = new GameLib::LineComponent(this, -1);
		mCircle = new GameLib::CircleLineComponent(this, -1);
	}

	EditingCircleBee::~EditingCircleBee()
	{
	}

	void EditingCircleBee::UpdateStageActor()
	{
		int num = GetDatas().size();

		if (num == 0)
		{
			Vec2 p(0.f, 0.f);
			mLine1->SetPoints(p, p);
			mCircle->SetRadius(0.f);
		}
		else if (num == 2)
		{
			Vec2 p1(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2(GetEditingScene()->GetCursorPos().x, GetEditingScene()->GetCursorPos().y);
			mLine1->SetPoints(p1, p2);

			Vec2 vec = p2 - p1;
			mCircle->SetAdjust(-1.f*vec);
			mCircle->SetRadius(vec.Length());

			float rot = GameLib::Math::Atan2(vec.x, vec.y);
			SetRotation(rot + GameLib::Math::Pi / 2.f);
		}
		else if (num >= 4)
		{
			Vec2 p1(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2(GetDatas().at(2), GetDatas().at(3));
			mLine1->SetPoints(p1, p2);

			Vec2 vec = p2 - p1;
			float rot;
			Vec2 pos;
			Vec2 ad;
			Vec2 point;

			if (num == 4)
				point = Vec2(GetEditingScene()->GetCursorPos().x, GetEditingScene()->GetCursorPos().y);
			else if (num == 6)
				point = Vec2(GetDatas().at(4), GetDatas().at(5));

			if (GameLib::Vector2::Cross(point - p1, p2 - p1) < 0.f)
			{
				rot = GameLib::Math::Atan2(vec.x, vec.y);
				ad = GameLib::Vector2::Rotation(GameLib::Vector2::Normalize(vec) * 20.f, -GameLib::Math::Pi / 2.f);
			}
			else
			{
				rot = GameLib::Math::Atan2(vec.x, vec.y) + GameLib::Math::Pi;
				ad = GameLib::Vector2::Rotation(GameLib::Vector2::Normalize(vec) * 20.f, GameLib::Math::Pi/2.f);
			}

			mCircle->SetAdjust(-1.f * ad - vec);
			float l = vec.Length();
			mCircle->SetRadius(GameLib::Math::Sqrt(20 * 20 + l * l));

			pos = p2 + ad;
			SetPosition(pos);
			SetRotation(rot);
		}
		
		
	}

	EditingItemCock::EditingItemCock(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"ItemCock",2)
	{
		SetScale(0.07f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Item/cock.png");

		mBody = new Game::Stage::Body(this, "ItemCock");
		mBody->SetWidthAndHeight(700.f, 700.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
	}

	EditingItemCock::~EditingItemCock()
	{
	}

	EditingItemWizard::EditingItemWizard(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"ItemWizard",2)
	{
		SetScale(0.07f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Item/witch.png");

		mBody = new Game::Stage::Body(this, "ItemWizard");
		mBody->SetWidthAndHeight(700.f, 700.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
	}

	EditingItemWizard::~EditingItemWizard()
	{
	}

	EditingItemAlien::EditingItemAlien(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"ItemAlien",2)
	{
		SetScale(0.07f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Item/alien.png");

		mBody = new Game::Stage::Body(this, "ItemAlien");
		mBody->SetWidthAndHeight(700.f, 700.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
	}

	EditingItemAlien::~EditingItemAlien()
	{
	}

	EditingContainer::EditingContainer(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Container",2)
	{
		SetScale(0.2f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Other/container.png");

		mBody = new Game::Stage::Body(this, "Container");
		mBody->SetWidthAndHeight(500.f, 500.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
	}

	EditingContainer::~EditingContainer()
	{
	}

	EditingMoveGround::EditingMoveGround(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"MoveGround",6)
	{
		mRect = new Game::Stage::RectangleComponent(this, 0.f, 0.f, Vec3(50.f, 50.f, 50.f));
		mBody = new Game::Stage::Body(this, "MoveGround");
		mBody->SetWidthAndHeight(0.f, 0.f);
		mBody->SetAdjust(Vec2(0.f, 0.f));
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));
		mLine = new GameLib::LineComponent(this);
		mLine->SetPoints(pos, pos);
	}

	EditingMoveGround::~EditingMoveGround()
	{
	}

	void EditingMoveGround::UpdateStageActor()
	{
		int size = GetDatas().size();

		if (size == 2)
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

			mLine->SetPoints(pos, pos);
		}
		else if (size >= 4)
		{

			Vec2 pos = GetPosition();

			Vec2 p1 = Vec2(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2 = Vec2(GetDatas().at(2), GetDatas().at(3));

			float w = GameLib::Math::Abs(p2.x - p1.x);
			float h = GameLib::Math::Abs(p2.y - p1.y);

			float minX = (p2.x < p1.x) ? p2.x : p1.x;
			float minY = (p2.y < p1.y) ? p2.y : p1.y;

			Vec2 topLeft(minX, minY);
			Vec2 posTopLeft(pos.x - w / 2.f, pos.y - h / 2.f);
			Vec2 vec = topLeft - posTopLeft;

			mRect->SetWidthAndHeight(w, h);
			mRect->SetAdjust(vec);

			mBody->SetWidthAndHeight(w, h);
			mBody->SetAdjust(vec);

			Vec2 point;
			if (size == 4)
				point = Vec2(GetEditingScene()->GetCursorPos().x, GetEditingScene()->GetCursorPos().y);
			else if (size == 6)
				point = Vec2(GetDatas().at(4), GetDatas().at(5));

			mLine->SetPoints(Vec2(minX + w / 2.f, minY + h / 2.f), point);
		}
	}

	EditingDiamond::EditingDiamond(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Diamond",2)
	{
		SetScale(0.07);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Item/diamond01.png");

		mBody = new Game::Stage::Body(this, "Diamond", 450.f, 600.f);
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));

	}

	EditingDiamond::~EditingDiamond()
	{
	}

	EditingStandLight::EditingStandLight(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"StandLight",2)
	{
		SetScale(0.12f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/StandLight/stem_sleep.png");

		mBody = new Game::Stage::Body(this, "StandLight", 600.f, 200.f);
		mBody->SetAdjust(Vec2(0.f, 290.f));
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));
		
	}

	EditingStandLight::~EditingStandLight()
	{
	}

	EditingCarrot::EditingCarrot(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Carrot",2)
	{
		SetScale(0.12f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/Carrot/stay.png");

		mBody = new Game::Stage::Body(this, "Carrot", 400.f, 300.f);
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));

	}

	EditingCarrot::~EditingCarrot()
	{
	}

	EditingDogu::EditingDogu(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Dogu",2)
	{
		SetScale(0.1f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Enemy/Dogu/stay.png");

		mBody = new Game::Stage::Body(this, "Dogu", 400.f, 700.f);
		mBody->SetColor(Vec3(0.f, 255.f, 0.f));
	}

	EditingDogu::~EditingDogu()
	{
	}

	EditingHeart::EditingHeart(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Heart",2)
	{
		SetScale(0.07f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Item/heart.png");

		mBody = new Game::Stage::Body(this, "Heart");
		mBody->SetWidthAndHeight(600.f, 500.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
	}

	EditingHeart::~EditingHeart()
	{
	}

	EditingWarp::EditingWarp(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Warp",4)
	{
		SetScale(0.1f);

		mTexture = new GameLib::TextureComponent(this, "../Assets/Other/warp.png");
		mTexture2 = new GameLib::TextureComponent(this, "../Assets/Other/warp.png");

		mBody = new Game::Stage::Body(this, "Warp", 500.f, 500.f);
		mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

		mBody2 = new Game::Stage::Body(this, "Warp", 500.f, 500.f);
		mBody2->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
	}

	EditingWarp::~EditingWarp()
	{
	}

	void EditingWarp::UpdateStageActor()
	{
		int size = GetDatas().size();

		if (size >= 2)
		{
			Vec2 p1(GetDatas().at(0), GetDatas().at(1));
			Vec2 p2;
			if (size == 2)
				p2 = GetPosition();
			else
				p2 = Vec2(GetDatas().at(2), GetDatas().at(3));

			Vec2 vec = (p2 - p1) / GetScale();

			mTexture2->SetAdjust(vec);
			mBody2->SetAdjust(vec);

			SetPosition(Vec2(GetDatas().at(0), GetDatas().at(1)));
		}
	}

	EditingGoal::EditingGoal(EditingScene* scene, const Vec2& pos)
		:EditingActor(scene,pos,"Goal",2)
	{
		SetScale(0.5f);

		auto texture1 = new GameLib::TextureComponent(this, "../Assets/Other/goal.png", -10);
		texture1->SetAdjust(GameLib::Vector2(-150.f, 0.f));

		auto texture2 = new GameLib::TextureComponent(this, "../Assets/Other/goal.png", 1200);
		texture2->SetAdjust(GameLib::Vector2(150.f, 0.f));

		auto body = new Game::Stage::Body(this, "Goal", 200.f, 500.f);
		body->SetAdjust(GameLib::Vector2(0.f, 130.f));
		body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
	}

	EditingGoal::~EditingGoal()
	{
	}

}

