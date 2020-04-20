#include"BackGroundLeaf.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"WindowData.hpp"



namespace Game
{
	namespace Stage
	{
		namespace BackGround
		{



			Leaf::Leaf(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:BackGroundActor(scene,pos,updateOrder)
			{
				int r = std::rand() % 100;
				SetRotation(GameLib::Math::TwoPi * r / 100.f);

				int r2 = std::rand() % 4;
				if (r2==0)
				{
					SetScale(0.03f);
					new GameLib::TextureComponent(this, "../Assets/BackGround/leaf-200.png", -65);
					SetRelativeMoveRate(0.75f);
				}
				else
				{
					SetScale(0.05f);
					new GameLib::TextureComponent(this, "../Assets/BackGround/leaf-160.png", -55);
					SetRelativeMoveRate(0.85f);
					
				}
			}

		

			Leaf::~Leaf()
			{
			}

			void Leaf::UpdateBackGround()
			{
				
				auto pos = GetPosition();
				GameLib::Vector2 v(-2.f, 0.5f);
				pos += v;
				if (pos.y > WINDOW_HEIGHT + 50.f)
					pos.y = -50.f;
				else if (pos.y < -50.f)
					pos.y = WINDOW_HEIGHT + 50.f;
			
				SetPosition(pos);

				SetRotation(GetRotation() + 0.05f);
				
				
			}


			Leaf2::Leaf2(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
				:BackGroundActor(scene, pos, updateOrder)
			{
				int r = std::rand() % 100;
				SetRotation(GameLib::Math::TwoPi * r / 100.f);

				int r2 = std::rand() % 4;

				if (r2==0)
				{
					SetScale(0.02f);
					new GameLib::TextureComponent(this, "../Assets/BackGround/leaf2-200.png", -65);
					SetRelativeMoveRate(0.75f);
				}
				else
				{
					SetScale(0.04f);
					new GameLib::TextureComponent(this, "../Assets/BackGround/leaf2-160.png", -55);
					SetRelativeMoveRate(0.85f);
					
				}
			}
			
			Leaf2::~Leaf2()
			{

			}

			void Leaf2::UpdateBackGround()
			{

				auto pos = GetPosition();
				GameLib::Vector2 v(-1.f, -1.f);
				pos += v;
				/*
				if (pos.y > WINDOW_HEIGHT + 50.f)
					pos.y -= WINDOW_HEIGHT + 100.f;
				else if (pos.y < -50.f)
					pos.y += WINDOW_HEIGHT + 100.f;

					*/
				while (pos.y <= -50.f)
				{
					float d = -50 - pos.y;
					pos.y = WINDOW_HEIGHT + 50.f - d;
				}
				while (WINDOW_HEIGHT+50.f < pos.x)
				{
					float  d = pos.y - WINDOW_HEIGHT + 50.f;
					pos.y = -50.f + d;
				}

				SetPosition(pos);

				SetRotation(GetRotation() + 0.05f);


			}
		}
	}
}