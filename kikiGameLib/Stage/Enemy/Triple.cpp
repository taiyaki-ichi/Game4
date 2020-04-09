#include"Triple.hpp"
#include"Stage/CollisionDetection/Body.hpp"
#include"EnemyState.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"Stage/CollisionDetection/Body.hpp"

namespace Game
{
	namespace Stage
	{
		namespace Enemy
		{
			using Vec2 = GameLib::Vector2;


			Triple::Triple(StageScene* scene, const GameLib::Vector2& pos)
				:StageActor(scene)
			{
				mState = new TripleActive(this);

				SetScale(0.10f);
				SetPosition(pos);

				std::vector<GameLib::Texture*> left = {
					GameLib::Data::GetTexture("../Assets/Enemy/Triple-left-001.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Triple-left-002.png")
				};
				std::vector<GameLib::Texture*> right = {
					GameLib::Data::GetTexture("../Assets/Enemy/Triple-right-001.png"),
					GameLib::Data::GetTexture("../Assets/Enemy/Triple-right-002.png")
				};
				std::vector<GameLib::Texture*> leftDeath = {
					GameLib::Data::GetTexture("../Assets/Enemy/Triple-death-left.png")
				};
				std::vector<GameLib::Texture*> rightDeath = {
					GameLib::Data::GetTexture("../Assets/Enemy/Triple-death-right.png")
				};
				std::vector<std::vector<GameLib::Texture*>> anim = {
					left,
					right,
					leftDeath,
					rightDeath
				};
				mAnim = new GameLib::AnimComponent(this);
				mAnim->SetAnimation(anim);
				mAnim->SetAnimFPS(16);

				mBody = new Body(this, "EnemyTriple");
				mBody->SetWidthAndHeight(350.f, 400.f);
				mBody->SetAdjust(GameLib::Vector2(0.f, 160.f));
				mBody->SetColor(GameLib::Vector3(0, 0, 255));

				mWeakness = new Body(this, "EnemyTripleWeakness");
				mWeakness->SetWidthAndHeight(350.f, 200.f);
				mWeakness->SetAdjust(GameLib::Vector2(0.f, -140.f));
				mWeakness->SetColor(GameLib::Vector3(255, 0, 0));
				
			}

			Triple::~Triple()
			{
				if (mState)
					delete mState;
			}

			void Triple::UpdateStageActor()
			{
				if (mState)
				{
					StageState* next = mState->Update();
					if (next != mState)
					{
						delete mState;
						mState = next;
					}
				}
			}

			void Triple::Hit(Body* myBody, Body* theBody)
			{
				if (mState)
					mState->Hit(myBody, theBody);
			}

			void Triple::SetAnimChannel(int i)
			{
				mAnim->SetChannel(i);
			}

			int Triple::GetAnimCannel() const
			{
				return mAnim->GetCannel();
			}

			void Triple::BreakBody()
			{
				mBody->SetWidthAndHeight(0.f, 0.f);
				mWeakness->SetWidthAndHeight(0.f, 0.f);
			}


			TripleActive::TripleActive(Triple* triple)
				:mTriple(triple)
				,mVelocity(-1.f)
				,mFlatFlag(false)
			{
			}

			TripleActive::~TripleActive()
			{
			}

			StageState* TripleActive::Update()
			{
				Vec2 pos = mTriple->GetPosition();
				pos.x += mVelocity;
				pos.y += GRAVITY;
				mTriple->SetPosition(pos);
				
				if (mVelocity > 0.f)
					mTriple->SetAnimChannel(1);
				else
					mTriple->SetAnimChannel(0);

				if (mFlatFlag)
					return new TripleFlat(mTriple);

				return this;
			}

			void TripleActive::Hit(Body* myBody, Body* theBody)
			{
				std::string name = theBody->GetName();
				std::string myName = myBody->GetName();
				GameLib::Actor* myActor = myBody->GetOwner();

				if (name == "EnemyTriple"&&myName=="EnemyTriple")
				{
					float x = theBody->GetOwner()->GetPosition().x - myActor->GetPosition().x;
					if (x > 0.f && mVelocity > 0.f)
						mVelocity *= -1.f;
					else if (x < 0.f && mVelocity < 0.f)
						mVelocity *= -1.f;

					GameLib::Vector2 adjust = GetAdjustUnrotatedRectVec(myBody, theBody);
					adjust.y = 0.f;
					myActor->SetPosition(myActor->GetPosition() + adjust);
				}
				else if (name == "Ground")
				{
					GameLib::Vector2 adjust = GetAdjustUnrotatedRectVecEx(myBody, theBody, GRAVITY, mVelocity);

					if (adjust.x > 0.f && mVelocity < 0.f)
						mVelocity *= -1.f;
					else if (adjust.x < 0.f && mVelocity>0.f)
						mVelocity *= -1.f;
					
					myActor->SetPosition(myActor->GetPosition() + adjust);
				}
				else if (name == "Player" && myName == "EnemyTripleWeakness")
				{
					mFlatFlag = true;
					mTriple->BreakBody();
				}
			}


			TripleFlat::TripleFlat(Triple* triple)
				:StageState()
				,mTriple(triple)
				,mCnt(0)
			{
				triple->SetAnimChannel(triple->GetAnimCannel() + 2);
				Vec2 pos = triple->GetPosition();
				pos.y += 10.f;
				triple->SetPosition(pos);

				triple->BreakBody();
			}

			TripleFlat::~TripleFlat()
			{
			}

			StageState* TripleFlat::Update()
			{
				mCnt++;
				if (mCnt > 90)
					mTriple->SetState(GameLib::Actor::State::Dead);

				return this;
			}

}

	}
}