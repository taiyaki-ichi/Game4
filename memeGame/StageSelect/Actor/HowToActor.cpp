#include"HowToActor.hpp"
#include"StageSelect/StageSelectScene.hpp"
#include"lib/include/Draw/AnimComponent.hpp"
#include"lib/include/Data.hpp"
#include"lib/include/Draw/TextComponent.hpp"

namespace Game
{
	namespace StageSelect
	{
		namespace HowTo
		{
			Left::Left(Scene* scene, const GameLib::Vector2& pos)
				:StageActor(scene,pos)
			{
				SetScale(0.07f);

				GameLib::Animation anim = {
					GameLib::Data::GetTexture("../Assets/tama/run001.png"),
					GameLib::Data::GetTexture("../Assets/tama/run002.png"),
					GameLib::Data::GetTexture("../Assets/tama/run003.png"),
				};
				auto a = new GameLib::AnimComponent(this, anim);
				a->SetAnimFPS(10);
				a->SetTextureFlip(GameLib::TextureFlip::Horizontal);

				auto actor = new Game::Stage::StageActor(scene, pos + GameLib::Vector2(0.f, 30.f));
				actor->SetScale(0.1f);
				new GameLib::TextureComponent(actor, "../Assets/Other/arrow.png");

				auto actor2 = new Game::Stage::StageActor(scene, pos + GameLib::Vector2(0.f, 60.f));
				
				auto t = new GameLib::TextComponent(actor2, "Assets/Font/mplus.ttf");
				t->SetText("A");

			}

			Left::~Left()
			{
			}

			Right::Right(Scene* scene, const GameLib::Vector2& pos)
				:StageActor(scene,pos)
			{
				SetScale(0.07f);

				GameLib::Animation anim = {
					GameLib::Data::GetTexture("../Assets/tama/run001.png"),
					GameLib::Data::GetTexture("../Assets/tama/run002.png"),
					GameLib::Data::GetTexture("../Assets/tama/run003.png"),
				};
				auto a = new GameLib::AnimComponent(this, anim);
				a->SetAnimFPS(10);

				auto actor = new Game::Stage::StageActor(scene, pos + GameLib::Vector2(0.f, 30.f));
				actor->SetScale(0.1f);
				auto te = new GameLib::TextureComponent(actor, "../Assets/Other/arrow.png");
				te->SetTextureFlip(GameLib::TextureFlip::Horizontal);

				auto actor2 = new Game::Stage::StageActor(scene, pos + GameLib::Vector2(0.f, 60.f));
				
				auto t = new GameLib::TextComponent(actor2, "Assets/Font/mplus.ttf");
				t->SetText("D");
			}

			Right::~Right()
			{
			}

			Jump::Jump(Scene* scene, const GameLib::Vector2& pos)
				:Stage::StageActor(scene,pos)
				,mVelocityY(-3.f)
				,mCnt(0)
			{
				SetScale(0.07f);

				GameLib::Animation up = {
					GameLib::Data::GetTexture("../Assets/tama/up.png"),
				};
				GameLib::Animation down = {
					GameLib::Data::GetTexture("../Assets/tama/down.png")
				};
				std::vector<GameLib::Animation> anim = { up,down };
				mAnim = new GameLib::AnimComponent(this, anim);

				auto actor = new Game::Stage::StageActor(scene, pos + GameLib::Vector2(0.f, 50.f));
				actor->SetScale(0.1f);
				auto te = new GameLib::TextureComponent(actor, "../Assets/Other/up.png");

				auto actor2 = new Game::Stage::StageActor(scene, pos + GameLib::Vector2(0.f, 100.f));

				auto t = new GameLib::TextComponent(actor2, "Assets/Font/mplus.ttf");
				t->SetText("SPACE");

 
			}

			Jump::~Jump()
			{
			}

			void Jump::UpdateStageActor()
			{

				if (mCnt > 15)
				{
					mVelocityY *= -1.f;
					mCnt = 0;
				}

				if (mVelocityY < 0.f)
					mAnim->SetChannel(0);
				else
					mAnim->SetChannel(1);

				auto pos = GetPosition();
				pos.y += mVelocityY;
				SetPosition(pos);

				mCnt++;
			}

		}
	}
}