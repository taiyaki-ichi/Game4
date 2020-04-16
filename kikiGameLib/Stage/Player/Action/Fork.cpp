#include"Fork.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/StageScene.hpp"
#include"lib/include/Data.hpp"

namespace Game
{
	namespace Stage
	{
		namespace PlayerAction
		{

			Fork::Fork(StageScene* scene, const GameLib::Vector2& pos, bool IsRight, int updateOrder)
				:StageStateActor(scene,pos,updateOrder)
			{
				SetScale(0.1f);

				mBody = new Body(this, "");
				mBody->SetWidthAndHeight(700.f, 100.f);
				mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

				SetStageState(new ForkActive(this,IsRight));

				mTexture = new GameLib::TextureComponent(this,-1);
				mTexture->SetDrawOrder(19);
			}

			Fork::~Fork()
			{
			}

			ForkActive::ForkActive(Fork* fork, bool IsRight)
				:StageState()
				,mFork(fork)
				,mCnt(0)
				,mIsRight(IsRight)
			{
			}

			ForkActive::~ForkActive()
			{
			}

			StageState* ForkActive::Update()
			{
				GameLib::Vector2 pos = mFork->GetPosition();

				if (mCnt == 2)
				{
					mFork->GetTextureComponent()->SetTexture(GameLib::Data::GetTexture("../Assets/Action/fork.png"));
					if (!mIsRight)
						mFork->GetTextureComponent()->SetTextureFlip(GameLib::TextureFlip::Horizontal);
					mFork->GetBody()->SetName("Fork");
				}
				else if (mCnt > 2)
				{
					if (mIsRight)
						pos.x += 7.f;
					else
						pos.x -= 7.f;
					mFork->SetPosition(pos);

				}

				if (pos.x < ActorUpdateScope::Left + 100.f ||
					ActorUpdateScope::Right - 100.f < pos.x)
					mFork->SetState(GameLib::Actor::State::Dead);

				mCnt++;
				return this;
			}

			void ForkActive::Hit(Body* myBody, Body* theBody)
			{
				std::string theName = theBody->GetName();
				std::string myName = myBody->GetName();

				//ˆê‰ñ–Ú‚Ì“–‚½‚è”»’è‚Å’n–Ê‚ÆÚG‚·‚éê‡‚Í¶¬‚µ‚È‚¢
				if (mCnt == 1 && theName == "Ground")
				{
					mFork->SetState(GameLib::Actor::State::Dead);
				}
				
				if (mCnt > 1)
				{
					if (theName == "Ground")
					{

						GameLib::Vector2 adjust = GetAdjustUnrotatedRectVec(myBody, theBody);

						if (GameLib::Math::Abs(adjust.x) < GameLib::Math::Abs(adjust.y) &&
							((adjust.x < 0.f && mIsRight) || (adjust.x > 0.f && !mIsRight)))
						{
							mFork->SetStageState(new ForkGround(mFork, theBody));
						}
						else
						{
							mFork->SetStageState(new ForkFall(mFork));
						}

					}
					else if (theName == "EnemyTriple" || theName == "EnemyTripleWeakness" ||
						theName == "EnemyFrog" || theName == "EnemyFrogWeakness"||
						theName=="EnemyBee"||theName=="EnemyBeeWeakness"||
						theName=="EnemyMaimai"||theName=="EnemyMaimaiWeakness")
					{
						mFork->SetStageState(new ForkFallTogether(mFork, theBody->GetStageOwner()));
					}
					else if (theName == "EnemyToge" || theName == "Container"||theName=="EnemyCarrot"||theName=="EnemyCarrotWeakness"||
						theName=="EnemyStandLight")
					{
						mFork->SetStageState(new ForkFall(mFork));
					}



				}

				
			}

			ForkFall::ForkFall(Fork* fork)
				:StageState()
				,mFork(fork)
				,mAdRot(0.05f)
			{
				mFork->GetBody()->SetWidthAndHeight(0.f, 0.f);
				if (mFork->GetTextureComponent()->GetTextureFlip() == GameLib::TextureFlip::Horizontal)
					mAdRot *= -1.f;
				
			}

			ForkFall::~ForkFall()
			{
			}

			StageState* ForkFall::Update()
			{
				GameLib::Vector2 pos = mFork->GetPosition();
				pos.y += 2.f;
				mFork->SetPosition(pos);

				float rot = mFork->GetRotation();
				rot += mAdRot;
				mFork->SetRotation(rot);

				if (pos.y > ActorUpdateScope::Bottom - 100.f ||
					pos.x > ActorUpdateScope::Right - 100.f ||
					pos.x < ActorUpdateScope::Left + 100.f)
					mFork->SetState(GameLib::Actor::State::Dead);

				return this;
			}

			ForkGround::ForkGround(Fork* fork,Body* grooundBody)
				:StageState()
				,mFork(fork)
				,mGroundBody(grooundBody)
				,mCnt(0)
			{
				mFork->GetBody()->SetName("ForkGround");
			}

			ForkGround::~ForkGround()
			{
			}

			StageState* ForkGround::Update()
			{
				if (mGroundBody)
				{
					auto pos = mFork->GetPosition();
					pos += mGroundBody->GetVelocity();
					mFork->SetPosition(pos);
				}

				if (mCnt >= 240 || !mGroundBody)
					return new ForkFall(mFork);

				mCnt++;
				return this;
			}

			void ForkGround::Hit(Body* myBody, Body* theBody)
			{
				if (theBody->GetName() == "Player")
				{
					mCnt += 3;
				}
			}

			ForkFallTogether::ForkFallTogether(Fork* fork, StageActor* together)
				:StageState()
				,mFork(fork)
				,mTogetherActor(together)
			{
				mAdjust = mFork->GetPosition() - mTogetherActor->GetPosition();
				mFork->GetBody()->SetWidthAndHeight(0.f, 0.f);
				
			}

			ForkFallTogether::~ForkFallTogether()
			{
			}

			StageState* ForkFallTogether::Update()
			{
				if (mTogetherActor)
				{

					float rot = mTogetherActor->GetRotation();
					mFork->SetRotation(rot);

					auto pos = mTogetherActor->GetPosition() + GameLib::Vector2::Rotation(mAdjust, rot);
					mFork->SetPosition(pos);

					if (pos.y > ActorUpdateScope::Bottom - 100.f ||
						pos.x > ActorUpdateScope::Right - 100.f ||
						pos.x < ActorUpdateScope::Left + 100.f)
						mFork->SetState(GameLib::Actor::State::Dead);
				}
				else
					mFork->SetState(GameLib::Actor::State::Dead);
					

				return this;
			}

}
	}
}