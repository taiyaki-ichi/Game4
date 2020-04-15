#include"Dogu.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/Player/Player.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{

			Dogu::Dogu(StageScene* scene, const GameLib::Vector2& pos,int updateOrder )
				:StageStateActor(scene,pos,updateOrder)
			{
				SetScale(0.1f);

				GameLib::Animation stay = {
					GameLib::Data::GetTexture("../Assets/Enemy/Dogu/stay.png"),
				};
				GameLib::Animation curse = {
					GameLib::Data::GetTexture("../Assets/Enemy/Dogu/curse.png")
				};
				std::vector<GameLib::Animation> anim = { stay,curse };
				mAnim = new GameLib::AnimComponent(this, anim);
				mAnim->SetDrawOrder(20);

				mBody = new Body(this, "EnemyDogu", 400.f, 700.f);
				mBody->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));

				SetStageState(new DoguState::Active(this));

			}

			Dogu::~Dogu()
			{
			}

			namespace DoguState
			{

				Active::Active(Dogu* dogu)
					: StageState()
					, mDogu(dogu)
					,mCnt(0)
				{
					mDogu->SetScale(0.1f);
					mDogu->GetAnim()->SetChannel(0);
					mDogu->GetBody()->SetWidthAndHeight(400.f, 700.f);
				}

				Active::~Active()
				{

				}

				StageState* Active::Update()
				{
					auto myPos = mDogu->GetPosition();
					auto playerPos = mDogu->GetStageScene()->GetPlayer()->GetPosition();
					auto vec = playerPos - myPos;
					auto ad = GameLib::Vector2(0.f, GameLib::Math::Sin(mCnt * 0.05f) * 0.5f);
					if (vec.Length() < ACTIVERANGE)
					{
						ad += GameLib::Vector2::Normalize(vec) * SPEED;
					}
					mDogu->SetPosition(myPos + ad);
					mCnt++;

					return this;
				}

				void Active::Hit(Body* myBody, Body* theBody)
				{
					std::string name = theBody->GetName();

					if (name == "Player")
					{
						mDogu->SetStageState(new Curse(mDogu));
					}
					else if (name == "Beam")
					{
						mDogu->SetState(GameLib::Actor::State::Dead);
					}
				}


				Curse::Curse(Dogu* dogu)
					:StageState()
					,mDogu(dogu)
					,mCnt(0)
				{
					mDogu->SetScale(0.5f);
					mDogu->GetAnim()->SetChannel(1);
					mDogu->GetBody()->SetWidthAndHeight(700.f, 700.f);
				}

				Curse::~Curse()
				{
				}

				StageState* Curse::Update()
				{
					if (mCnt > 60)
						return new Active(mDogu);

					mCnt++;
					return this;
				}

				void Curse::Hit(Body* myBody, Body* theBody)
				{
					std::string name = theBody->GetName();

					if (name == "Player")
						mCnt = 0;
					else if (name == "Beam")
					{
						mDogu->SetState(GameLib::Actor::State::Dead);
					}
				}

			}

		}

	}
}
