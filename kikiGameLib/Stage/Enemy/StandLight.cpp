#include"StandLight.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Data.hpp"
#include"Stage/StageScene.hpp"
#include"Stage/Player.hpp"
#include"Stage/Enemy/EnemyState.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{
			using Vec2 = GameLib::Vector2;


			StandLight::StandLight(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:StageActor(scene,pos,updateOrder)
				,mCnt(0)
				,mHeadDeathFlag(false)
			{
				SetScale(0.12f);

				mHead = new StandLightParts::Head(scene, this, pos - Vec2(0.f, 50.f));

				GameLib::Animation sleep = {
					GameLib::Data::GetTexture("../Assets/Enemy/StandLight/stem_sleep.png"),
				};
				GameLib::Animation stand = {
					GameLib::Data::GetTexture("../Assets/Enemy/StandLight/stem_stand.png"),
				};
				std::vector<GameLib::Animation> anim = { sleep,stand };

				mAnim = new GameLib::AnimComponent(this, anim);
				mAnim->SetDrawOrder(20);

				mStemBody = new Body(this, "");
				mStemBody->SetWidthAndHeight(600.f, 200.f);
				mStemBody->SetAdjust(Vec2(0.f, 290.f));
				mStemBody->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));
			}

			StandLight::~StandLight()
			{
			}

			void StandLight::UpdateStageActor()
			{
				auto playerPos = GetStageScene()->GetPlayer()->GetPosition();
				auto myPos = GetPosition();

				myPos.y += 5.f;
				SetPosition(myPos);

	
				if (!mHeadDeathFlag)
				{
					if (mHead->GetAnim()->GetCannel() != 4)
					{
						if (mHead->GetAnim()->GetCannel() == 3)
						{
							mAnim->SetChannel(0);
							mHead->SetPosition(myPos + Vec2(0.f, 10.f));
						}
						else if ((playerPos - myPos).Length() > StandLightParts::ACTIVERANGE + 20.f)
						{
							mAnim->SetChannel(0);
							mHead->SetPosition(myPos + Vec2(0.f, 10.f));
							if (mHead->GetAnim()->GetCannel() == 1 || mHead->GetAnim()->GetCannel() == 2)
								mHead->SetStageState(new StandLightParts::HeadSleep(mHead));
						}
						else if ((playerPos - myPos).Length() < StandLightParts::ACTIVERANGE - 20.f)
						{
							mAnim->SetChannel(1);
							mHead->SetPosition(myPos + Vec2(0.f, -50.f));
							if (mHead->GetAnim()->GetCannel() == 0)
								mHead->SetStageState(new StandLightParts::HeadActive(mHead));
						}
					}
					else
					{
						mAnim->SetChannel(0);
					}
				}
				else
				{
					mAnim->SetChannel(0);
				}
				

				mCnt++;

			}

			void StandLight::Hit(Body* myBody, Body* theBody)
			{

				std::string name = theBody->GetName();

				if (name == "Ground"||name=="Container")
				{
					auto vec = GetAdjustUnrotatedRectVecEx(myBody, theBody, 0.f, 0.f);
					if (vec.y < 0.f)
						vec += theBody->GetVelocity();
					SetPosition(GetPosition() + vec);
				}
			}

			namespace StandLightParts
			{

				Head::Head(StageScene* scene, StandLight* stem, const GameLib::Vector2& pos, int updateOeder)
					:StageStateActor(scene,pos,updateOeder)
					,mStem(stem)
				{

					SetScale(0.18);

					GameLib::Animation sleep = {
						GameLib::Data::GetTexture("../Assets/Enemy/StandLight/head_sleep.png"),
					};
					GameLib::Animation active = {
						GameLib::Data::GetTexture("../Assets/Enemy/StandLight/head_active.png"),
					};
					GameLib::Animation beam = {
						GameLib::Data::GetTexture("../Assets/Enemy/StandLight/head_beam.png"),
					};
					GameLib::Animation death = {
						GameLib::Data::GetTexture("../Assets/Enemy/StandLight/head_death.png"),
					};
					GameLib::Animation biku = {
						GameLib::Data::GetTexture("../Assets/Enemy/StandLight/head_biku.png"),
					};

					std::vector<GameLib::Animation> anim = { sleep,active,beam,death ,biku };

					mAnim = new GameLib::AnimComponent(this, anim);
					mAnim->SetDrawOrder(21);

					mBody = new Body(this, "EnemyStandLight");
					mBody->SetWidthAndHeight(300.f, 200.f);
					mBody->SetAdjust(Vec2(-30.f, 0.f));
					mBody->SetColor(GameLib::Vector3(255.f, 0.f, 0.f));

					SetStageState(new HeadActive(this));

				}

				Head::~Head()
				{
				}

				void Head::BreakBody()
				{
					mBody->SetWidthAndHeight(0.f, 0.f);
				}

				void Head::HeadDead()
				{
					mStem->HeadDead();
				}

				const int HeadActive::BEAMTIME = 120;
				const int HeadActive::COOLTIME = 180;

				HeadActive::HeadActive(Head* head)
					:StageState()
					,mHead(head)
					,mCnt(0)
				{
					mHead->GetAnim()->SetTextureFlip(GameLib::TextureFlip::None);
					mHead->GetAnim()->SetChannel(1);
					mHead->GetBody()->SetAdjust(Vec2(-30.f, 0.f));
				}

				HeadActive::~HeadActive()
				{
				}

				StageState* HeadActive::Update()
				{
					auto playerPos = mHead->GetStageScene()->GetPlayer()->GetPosition();
					auto myPos = mHead->GetPosition();

					auto vec = playerPos - myPos;
					float rot = GameLib::Math::Atan2(vec.x, vec.y);

					float pi = GameLib::Math::Pi;
					if (0.f < rot &&rot<pi)
					{
						mHead->GetAnim()->SetTextureFlip(GameLib::TextureFlip::Horizontal);
						mHead->GetBody()->SetAdjust(Vec2(30.f, 0.f));
						rot += pi;
					}
					else
					{
						mHead->GetAnim()->SetTextureFlip(GameLib::TextureFlip::None);
						mHead->GetBody()->SetAdjust(Vec2(-30.f, 0.f));
					}
					mHead->SetRotation(rot + pi / 2.f);

					if (COOLTIME < mCnt&&mCnt%5==0)
					{
						new Spore(mHead->GetStageScene(), myPos, Vec2::Normalize(vec) * 5.f);
					}

					if (mCnt == COOLTIME + 1)
						mHead->GetAnim()->SetChannel(2);
					else if (mCnt > COOLTIME + BEAMTIME)
					{
						mCnt = 0;
						mHead->GetAnim()->SetChannel(1);
					}
					mCnt++;

					return this;
				}

				void HeadActive::Hit(Body* myBody, Body* theBody)
				{
					ActiveAndSleepHit(mHead, myBody, theBody);
				}

				HeadSleep::HeadSleep(Head* head)
					:StageState()
					,mHead(head)
				{

					mHead->GetAnim()->SetChannel(0);
					mHead->GetAnim()->SetTextureFlip(GameLib::TextureFlip::Horizontal);
					mHead->GetBody()->SetAdjust(Vec2(30.f, 0.f));
				}

				HeadSleep::~HeadSleep()
				{
				}

				StageState* HeadSleep::Update()
				{
					auto playerPos = mHead->GetStageScene()->GetPlayer()->GetPosition();
					auto myPos = mHead->GetPosition();

					return this;
				}

				void HeadSleep::Hit(Body* myBody, Body* theBody)
				{
					ActiveAndSleepHit(mHead, myBody, theBody);
				}

				HeadDeath::HeadDeath(Head* head)
					:StageState()
					,mHead(head)
					,mCnt(0)
				{
					mHead->GetAnim()->SetChannel(3);
					mHead->GetAnim()->SetTextureFlip(GameLib::TextureFlip::Horizontal);
					mHead->GetBody()->SetAdjust(Vec2(30.f, 0.f));
				}

				HeadDeath::~HeadDeath()
				{
				}

				StageState* HeadDeath::Update()
				{
					if (mCnt > 300)
					{
						return new HeadActive(mHead);
					}
					mCnt++;

					return this;
				}

				void HeadDeath::Hit(Body* myBody, Body* theBody)
				{
					std::string name = theBody->GetName();

					if (name == "Beam" || name == "Meteor")
					{
						mHead->GetAnim()->SetChannel(4);
						mHead->BreakBody();
						mHead->HeadDead();
						mHead->SetStageState(new Fall(mHead));
					}
				}

				void ActiveAndSleepHit(Head* head,Body* myBody, Body* theBody)
				{
					std::string name = theBody->GetName();

					if (name == "Player")
					{
						head->SetStageState(new HeadDeath(head));
					}
					else if (name == "Beam"||name=="Meteor")
					{
						head->GetAnim()->SetChannel(4);
						head->BreakBody();
						head->HeadDead();
						head->SetStageState(new Fall(head));
					}
				}

				Spore::Spore(StageScene* scene, const GameLib::Vector2& pos, const GameLib::Vector2& velocity, int updateOrder)
					:StageActor(scene,pos,updateOrder)
					,mVelocity(velocity)
				{
					SetScale(0.04f);

					auto tex=new GameLib::TextureComponent(this, "../Assets/Enemy/StandLight/spore.png");
					tex->SetDrawOrder(20);

					auto body = new Body(this, "Spore", 250.f, 250.f);
					body->SetColor(GameLib::Vector3(0.f, 0.f, 255.f));
				}

				Spore::~Spore()
				{
				}

				void Spore::UpdateStageActor()
				{
					auto pos = GetPosition();
					pos += mVelocity;
					SetPosition(pos);

					SetRotation(GetRotation() + 0.01f);
					
					if (ActorUpdateScope::Left + 100.f > pos.x || ActorUpdateScope::Right - 100.f < pos.x ||
						ActorUpdateScope::Top + 100.f > pos.y || ActorUpdateScope::Bottom - 100.f < pos.y)
						SetState(GameLib::Actor::State::Dead);
						
				}

}

		}
	}
}

