#pragma once
#include"Stage/StageActor.hpp"
namespace GameLib
{
	class AnimComponent;
	class TextureComponent;
}

namespace Game
{
	namespace Stage
	{
		class Player;
		class StageScene;

		namespace PlayerLifeParts
		{
			class Heart : GameLib::Actor
			{
			public:
				Heart(GameLib::Scene* scene,const GameLib::Vector2& pos, int updateOerde = 0);
				virtual ~Heart();

				virtual void Update() override;

				void Break();

				
			};
		}

		class PlayerLife : public GameLib::Actor
		{
		public:

			const static int LIFEMAX;
			const static int INVINCIBLETIME;

			PlayerLife(GameLib::Scene* scene,Player* player, int dorawOrder = 0);
			virtual ~PlayerLife();

			virtual void Update() override;

			void Damage(int num = 1);
			void Heal(int num = 1);

			bool GetInvincibleFlag() const { return mInvincibleFlag; }

		private:
			Player* mPlayer;
			GameLib::TextureComponent* mTexture;

			std::vector<PlayerLifeParts::Heart*> mHearts;

			//–³“G‚©‚Ç‚¤‚©
			bool mInvincibleFlag;
			int mCnt;
		};

	}
}