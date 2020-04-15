#include"PlayerLife.hpp"
#include"Stage/StageScene.hpp"
#include"lib/include/Draw/TextComponent.hpp"
#include"Player.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"

namespace Game
{
	namespace Stage
	{

		namespace PlayerLifeParts
		{


			Heart::Heart(GameLib::Scene* scene, const GameLib::Vector2& pos, int updateOerde)
				:GameLib::Actor(scene,updateOerde)
			{
				SetPosition(pos);
				SetScale(0.05f);

				GameLib::TextureComponent* texture = new GameLib::TextureComponent(this, "../Assets/Item/heart.png");

			}


			Heart::~Heart()
			{
			}

			void Heart::Update()
			{
			}

			void Heart::Break()
			{
				SetState(GameLib::Actor::State::Dead);
			}

		}

		const int PlayerLife::LIFEMAX = 3;
		const int PlayerLife::INVINCIBLETIME = 30;

		PlayerLife::PlayerLife(GameLib::Scene* scene, Player* player, int dorawOrder)
			:GameLib::Actor(scene)
			,mPlayer(player)
			,mCnt(-1)
			,mInvincibleFlag(false)
		{
			GameLib::Vector2 pos = GameLib::Vector2(16.f, 16.f);
			SetPosition(pos);
			SetScale(0.07f);

			mTexture = new GameLib::TextureComponent(this, "../Assets/tama/icon.png");
			
			for (int i = 0; i < 3; i++)
			{
				pos += GameLib::Vector2(32.f, 0.f);
				mHearts.emplace_back(new PlayerLifeParts::Heart(scene, pos));
				
			}
		}

		PlayerLife::~PlayerLife()
		{
		}

		void PlayerLife::Update()
		{
			if (mCnt > INVINCIBLETIME)
			{
				mCnt = -1;
				mInvincibleFlag = false;
				mPlayer->GetBody()->SetName("Player");
			}

			if (mCnt >= 0)
				mCnt++;

		}

		void PlayerLife::Damage(int num )
		{
			mCnt = 0;
			mInvincibleFlag = true;
			mPlayer->GetBody()->SetName("");

			for (int i = 0; i < num; i++)
			{
				int heartNum = mHearts.size();
				if (heartNum <= 0)
				{
					mPlayer->SetStageState(new PlayerState::Death(mPlayer));
					break;
				}

				mHearts.back()->Break();
				mHearts.pop_back();

			}
		}

		void PlayerLife::Heal(int num )
		{

			for (int i = 0; i < num; i++)
			{
				int heartNum = mHearts.size();
				if (heartNum >= LIFEMAX)
					break;

				GameLib::Vector2 pos = GetPosition() + GameLib::Vector2(32.f, 0.f) * static_cast<float>(heartNum+1);
				mHearts.emplace_back(new PlayerLifeParts::Heart(GetScene(), pos));
			}
		}

	}
}


