#include"Ground.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"Stage/StageScene.hpp"

#include<iostream>

namespace Game
{
	namespace Stage
	{
		Ground::Ground(StageScene* scene,const GameLib::Vector2& pos, float width, float height, int updateOrder)
			:StageActor(scene,pos,updateOrder)
			,mBreakFlag(false)
			,mIsUnbreakable(false)
		{
			mBody = new Body(this, "Ground", width, height);
			mBody->SetColor(GameLib::Color::Black);

			using Vec3 = GameLib::Vector3;
			new RectangleComponent(this, width, height, Vec3(50.f, 50.f, 50.f));

		}

		Ground::~Ground()
		{
		}

		void Ground::UpdateStageActor()
		{
			UpdateGround();


			if (mBreakFlag)
			{
				SetState(GameLib::Actor::State::Dead);
				mBody->SetWidthAndHeight(0.f, 0.f);
			}

			if (mBody->GetHeight() <= 5.f || mBody->GetWidth() <= 5.f)
			{
				SetState(Actor::State::Dead);
				mBody->SetWidthAndHeight(0.f, 0.f);
			}
		}

		void Ground::Hit(Body* myBody, Body* theBody)
		{
			std::string name = theBody->GetName();

			if (name == "Beam"&&!mIsUnbreakable&&!mBreakFlag)
			{
				BeamHit(this, myBody, theBody);
			}
		}

		void Ground::CreateGround(const GameLib::Vector2& pos, float w, float h)
		{
			auto g = new Ground(GetStageScene(), pos, w, h);
		}

		void BeamHit(Ground* myGround, Body* myBody, Body* theBody)
		{
			using Vec2 = GameLib::Vector2;

			Vec2 pos = myGround->GetPosition();
			Vec2 thePos = theBody->GetOwner()->GetPosition();
			thePos += theBody->GetAdjust();
			float line = 1.f;

			float myLeft = pos.x - myBody->GetWidth() / 2.f;
			float myRight = pos.x + myBody->GetWidth() / 2.f;
			float myTop = pos.y - myBody->GetHeight() / 2.f;
			float myButtom = pos.y + myBody->GetHeight() / 2.f;
			float theLeft = thePos.x - theBody->GetWidth() / 2.f;
			float theRight = thePos.x + theBody->GetWidth() / 2.f;
			float theTop = thePos.y - theBody->GetHeight() / 2.f;
			float theButtom = thePos.y + theBody->GetHeight() / 2.f;

			float w, h;

			if (theTop - myTop > line&& myButtom - theButtom > line)
			{
				h = theTop - myTop;
				w = myRight - myLeft;
				myGround->CreateGround(Vec2(myLeft + w / 2.f, myTop + h / 2.f), w, h);
				h = myButtom - theButtom;
				myGround->CreateGround(Vec2(myLeft + w / 2.f, theButtom + h / 2.f), w, h);

				h = theButtom - theTop;
				if (theLeft - myLeft > line)
				{
					w = theLeft - myLeft;
					//Beam‚Æd‚È‚ç‚È‚¢‚æ‚¤‚É‚·‚é‚½‚ß­‚µ‚¸‚ç‚·
					myGround->CreateGround(Vec2(myLeft + w / 2.f - 1.f, theTop + h / 2.f), w - 2.f, h);
				}
				if (myRight - theRight > line)
				{
					w = myRight - theRight;
					myGround->CreateGround(Vec2(theRight + w / 2.f + 1.f, theTop + h / 2.f), w - 2.f, h);
				}

			}
			else if (theTop - myTop > line)
			{
				h = theTop - myTop;
				w = myRight - myLeft;
				if (w > line&& h > line)
					myGround->CreateGround(Vec2(myLeft + w / 2.f, myTop + h / 2.f), w, h);

				h = myButtom - theTop;
				if (theLeft - myLeft > line)
				{
					w = theLeft - myLeft;
					myGround->CreateGround(Vec2(myLeft + w / 2.f - 1.f, theTop + h / 2.f), w - 2.f, h);
				}

				if (myRight - theRight > line)
				{
					w = myRight - theRight;
					myGround->CreateGround(Vec2(theRight + w / 2.f + 1.f, theTop + h / 2.f), w - 2.f, h);
				}

			}
			else if (myButtom - theButtom > line)
			{
				h = myButtom - theButtom;
				w = myRight - myLeft;
				if (w > line&& h > line)
					myGround->CreateGround(Vec2(myLeft + w / 2.f, theButtom + h / 2.f), w, h);

				h = theButtom - myTop;
				if (theLeft - myLeft > line)
				{
					w = theLeft - myLeft;
					myGround->CreateGround(Vec2(myLeft + w / 2.f - 1.f, myTop + h / 2.f), w - 2.f, h);
				}

				if (myRight - theRight > line)
				{
					w = myRight - theRight;
					myGround->CreateGround(Vec2(theRight + w / 2.f + 1.f, myTop + h / 2.f), w - 2.f, h);
				}

			}
			else //if(Math::Abs(theTop - myTop)<=line&&Math::Abs(myButtom - theButtom)<=line)
			{
				h = myButtom - myTop;
				w = theLeft - myLeft;
				if (h > line&& w > line)
				{
					myGround->CreateGround(Vec2(myLeft + w / 2.f - 1.f, myTop + h / 2.f), w - 2.f, h);
				}

				w = myRight - theRight;
				if (h > line&& w > line)
				{
					myGround->CreateGround(Vec2(theRight + w / 2.f + 1.f, myTop + h / 2.f), w - 2.f, h);
				}

			}

			myGround->BreakNextUpdate();
		}

	}
}