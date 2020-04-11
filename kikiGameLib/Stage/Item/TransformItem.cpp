#include"TransformItem.hpp"
#include<string>
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextureComponent.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Item
		{

			TransformItem::TransformItem(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:StageActor(scene,pos,updateOrder)
				,mCnt(0)
			{
			}

			TransformItem::~TransformItem()
			{
			}

			void TransformItem::UpdateStageActor()
			{
				GameLib::Vector2 pos = GetPosition();
				GameLib::Vector2 ad = GameLib::Vector2(0.f, GameLib::Math::Sin(mCnt * 0.05f) * 0.2f);
				SetPosition(pos + ad);

				mCnt++;
			}

			void TransformItem::Hit(Body* myBody, Body* theBody)
			{
				std::string name = theBody->GetName();

				if (name == "Player")
				{
					SetState(Actor::State::Dead);
				}
			}

			Cock::Cock(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:TransformItem(scene,pos,updateOrder)
			{
				SetScale(0.07f);

				GameLib::TextureComponent* texture = new GameLib::TextureComponent(this, "../Assets/Item/cock.png");

				Body* body = new Body(this, "ItemCock");
				body->SetWidthAndHeight(700.f, 700.f);
				body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
			}

			Cock::~Cock()
			{
			}



			Wizard::Wizard(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:TransformItem(scene,pos,updateOrder)
			{
				SetScale(0.07f);

				GameLib::TextureComponent* texture = new GameLib::TextureComponent(this, "../Assets/Item/witch.png");

				Body* body = new Body(this, "ItemWizard");
				body->SetWidthAndHeight(700.f, 700.f);
				body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
			}


			Wizard::~Wizard()
			{
			}

			Alien::Alien(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:TransformItem(scene,pos,updateOrder)
			{
				SetScale(0.07f);

				GameLib::TextureComponent* texture = new GameLib::TextureComponent(this, "../Assets/Item/alien.png");

				Body* body = new Body(this, "ItemAlien");
				body->SetWidthAndHeight(700.f, 700.f);
				body->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
			}

			Alien::~Alien()
			{
			}

		}
	}
}