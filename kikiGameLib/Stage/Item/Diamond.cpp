#include"Diamond.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Item
		{



			Diamond::Diamond(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:StageActor(scene,pos,updateOrder)
			{

				SetScale(0.07f);

				GameLib::Animation anim = {
					GameLib::Data::GetTexture("../Assets/Item/diamond01.png"),
					GameLib::Data::GetTexture("../Assets/Item/diamond02.png"),
					GameLib::Data::GetTexture("../Assets/Item/diamond04.png"),
					GameLib::Data::GetTexture("../Assets/Item/diamond03.png"),
				};
				auto a = new GameLib::AnimComponent(this, anim);
				a->SetAnimFPS(6);

				mBody = new Body(this, "Diamond", 450.f, 600.f);
				mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

			}

			Diamond::~Diamond()
			{
			}

			void Diamond::Hit(Body* myBody, Body* theBody)
			{
				std::string name = theBody->GetName();

				/*
				if (name == "Player")
				{
					mBody->SetWidthAndHeight(0.f, 0.f);
					SetState(GameLib::Actor::State::Dead);
				}
				*/
			}

		}
	}
}