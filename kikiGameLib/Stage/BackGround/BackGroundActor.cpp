#include"BackGroundActor.hpp"
#include"WindowData.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"BackGroundBasis.hpp"

namespace Game
{
	namespace Stage
	{

		

		BackGroundActor::BackGroundActor(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
			:StageActor(scene,pos,updateOrder)
		{
		}

		BackGroundActor::~BackGroundActor()
		{
		}

		void BackGroundActor::UpdateStageActor()
		{
			auto pos = GetPosition();

			if (pos.x <= -WINDOW_WIDTH * 0.5f)
			{
				float d = -WINDOW_WIDTH * 0.5f - pos.x;
				pos.x = WINDOW_WIDTH * 1.5f - d;
				SetPosition(pos);
			}
			else if (WINDOW_WIDTH * 1.5 < pos.x)
			{
				float  d = pos.x - WINDOW_WIDTH * 1.5f;
				pos.x = -WINDOW_WIDTH * 0.5f + d;
				SetPosition(pos);
			}
		}

		void CreateBackGrounds(StageScene* scene, const std::string& fileName, int num, float posY, float relativeRate, float drawOrder, float scele)
		{
			float d = WINDOW_WIDTH * 2.f / static_cast<float>(num);
			BackGroundActor* actor;
			for (int i = 0; i < num; i++)
			{
				actor = new BackGroundActor(scene, GameLib::Vector2(-WINDOW_WIDTH * 0.5f + d * i, posY));
				actor->SetScale(scele);
				actor->SetRelativeMoveRate(relativeRate);
				new GameLib::TextureComponent(actor, fileName, drawOrder);
			}

		}

		void CreateForestBackGround(StageScene* scene)
		{
			new BackGroundBasis(scene);
			new Horaizon180(scene);
			new Horaizon230(scene);
			CreateBackGrounds(scene, "../Assets/BackGround/tree-130.png", 5, 250.f, 0.8f, -50, 0.5f);
			CreateBackGrounds(scene, "../Assets/BackGround/tree-180.png", 8, 200.f, 0.6f, -60, 0.3f);
			CreateBackGrounds(scene, "../Assets/BackGround/mountain-230.png", 5, 0.f, 0.4f, -70, 0.6f);
			auto a = new BackGroundActor(scene, GameLib::Vector2(700.f, 100.f));
			a->SetRelativeMoveRate(0.05f);
			a->SetScale(0.6f);
			new GameLib::TextureComponent(a, "../Assets/BackGround/moon-230.png", -80);
		}

	}
}