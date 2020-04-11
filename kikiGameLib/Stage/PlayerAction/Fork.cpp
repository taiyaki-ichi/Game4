#include"Fork.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/StageScene.hpp"

namespace Game
{
	namespace Stage
	{
		namespace PlayerAction
		{

			Fork::Fork(StageScene* scene, const GameLib::Vector2& pos, bool IsRight, int updateOrder)
				:StageStateActor(scene,pos,updateOrder)
			{
				SetScale(0.01f);

				mBody = new Body(this, "");
				mBody->SetWidthAndHeight(700.f, 150.f);
				mBody->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));

				SetStageState(new ForkActive(this,IsRight));
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


				if (mCnt == 2)
				{
					auto texture = new GameLib::TextureComponent(mFork, "..Assets/Attack/fork.png");
					if (!mIsRight)
						texture->SetTextureFlip(GameLib::TextureFlip::Horizontal);

					mFork->GetBody()->SetName("Fork");
				}
				else if (mCnt > 2)
				{

					GameLib::Vector2 pos = mFork->GetPosition();
					if (mIsRight)
						pos.x += 7.f;
					else
						pos.x -= 7.f;
					mFork->SetPosition(pos);

				}



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
							//ForkGround
						}
						else
						{
							//Fall
						}

					}

					//if name==teki
					//togettherfall



				}

				
			}

			ForkFall::ForkFall(Fork* fork, bool isRight)
				:StageState()
				,mFork(fork)
				,mIsRight(isRight)
			{
				mFork->GetBody()->SetWidthAndHeight(0.f, 0.f);
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
				if (mIsRight)
					rot += 0.05f;
				else
					rot -= 0.05f;
				mFork->SetRotation(rot);

				if (pos.y > ActorUpdateScope::Bottom - 100.f ||
					pos.x > ActorUpdateScope::Right - 100.f ||
					pos.x < ActorUpdateScope::Left + 100.f)
					mFork->SetState(GameLib::Actor::State::Dead);

				return this;
			}

}
	}
}