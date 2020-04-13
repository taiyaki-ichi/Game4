#include"Beam.hpp"
#include"lib/include/Draw/LineComponent.hpp"
#include"Stage/Draw/RectangleComponent.hpp"
#include"lib/include/Draw/TextureComponent.hpp"
#include"Stage/CollisionDetection/Body.hpp"

#include"lib/include/InputState.hpp"

namespace Game
{
	namespace Stage
	{
		namespace PlayerAction
		{
			int Beam::mBeamNum = 0;

			using Vec2 = GameLib::Vector2;

			Beam::Beam(StageScene* scene, const GameLib::Vector2& pos, bool isRight, int updateOrder)
				:StageActor(scene, pos, updateOrder)
				, mCnt(0)
				, mIsRight(isRight)
			{
				new BeamEffect::Charge(scene, pos);
				mBeamNum++;

			}
			Beam::~Beam()
			{
				mBeamNum--;
			}
			void Beam::UpdateStageActor()
			{
				if (mCnt == 60)
					new BeamEffect::Zyu(GetStageScene(), GetPosition());

				if (mCnt == 90)
				{
					new BeamEffect::Line(GetStageScene(), GetPosition(), mIsRight);
				}
				if (mCnt > 120)
					SetState(GameLib::Actor::State::Dead);
				mCnt++;
			}


			namespace BeamEffect
			{



				LineCharge::LineCharge(StageScene* scene, const GameLib::Vector2& pos, const GameLib::Vector2& center, int updateOrder)
					:StageActor(scene, center, updateOrder)
					, mLinePos(pos)
				{
					Vec2 vec = center - pos;
					float rot = GameLib::Math::Atan2(vec.x, vec.y);
					SetRotation(rot);

					mLine = new GameLib::LineComponent(this);
					mLine->SetPoints(pos + Vec2::Normalize(vec) * 10.f, pos);
				}

				LineCharge::~LineCharge()
				{
				}

				void LineCharge::UpdateStageActor()
				{
					Vec2 pos = GetPosition();
					Vec2 vec = pos - mLinePos;

					float lineLen = 20.f;
					float speed = 5.f;

					Vec2 p2 = mLinePos + Vec2::Normalize(vec) * lineLen;
					mLine->SetPoints(mLinePos, p2);
					mLinePos += Vec2::Normalize(vec) * speed;


					if ((mLinePos - pos).Length() < 10.f)
						SetState(GameLib::Actor::State::Dead);
				}

				void LineCharge::AdjustPosSub(const GameLib::Vector2& vec)
				{
					mLinePos += vec;
				}

				RectCharge::RectCharge(StageScene* scene, const GameLib::Vector2& pos, const GameLib::Vector2& center, int updateOrder)
					:StageActor(scene, pos, updateOrder)
					, mCenter(center)
				{
					mRect = new RectangleComponent(this, 10.f, 10.f, GameLib::Color::Black);

				}

				RectCharge::~RectCharge()
				{
				}

				void RectCharge::UpdateStageActor()
				{
					Vec2 pos = GetPosition();
					Vec2 vec = mCenter - pos;

					float speed = 4.f;

					Vec2 nextPos = pos + Vec2::Normalize(vec) * speed;
					SetPosition(nextPos);

					float rot = GetRotation();
					rot += 0.5f;
					SetRotation(rot);

					if ((nextPos - mCenter).Length() < 10.f)
						SetState(GameLib::Actor::State::Dead);
				}

				void RectCharge::AdjustPosSub(const GameLib::Vector2& vec)
				{
					mCenter += vec;
				}

				Charge::Charge(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
					:StageActor(scene, pos, updateOrder)
					, mCnt(0)
				{
				}

				Charge::~Charge()
				{
				}

				void Charge::UpdateStageActor()
				{
					Vec2 center = GetPosition();

					int r = std::rand() % 100;
					float rot = r * GameLib::Math::TwoPi / 100.f;
					Vec2 vec = Vec2::Rotation(Vec2(110.f, 0.f), rot);

					Vec2 p = center + vec;
					new LineCharge(GetStageScene(), p, center);


					r = std::rand() % 100;
					if (r % 5 == 0)
					{
						rot = r * GameLib::Math::TwoPi / 100.f;
						vec = Vec2::Rotation(Vec2(150.f, 0.f), rot);
						p = center + vec;
						new RectCharge(GetStageScene(), p, center);
					}

					if (mCnt > 60)
						SetState(GameLib::Actor::State::Dead);

					mCnt++;

				}

				Zyu::Zyu(StageScene* scene, const GameLib::Vector2& pos, int updateOrder)
					:StageActor(scene, pos, updateOrder)
					, mCnt(0)
				{
					new GameLib::TextureComponent(this, "../Assets/Action/guruguru.png",20);
					SetScale(0.f);
				}

				Zyu::~Zyu()
				{
				}

				void Zyu::UpdateStageActor()
				{

					float sca = GetScale();
					float rot = GetRotation();
					if (mCnt < 30)
					{
						sca += 0.00001f;

						rot += 0.001f;

					}
					else if (mCnt < 80)
					{
						sca += 0.1f;
						if (sca > 1.0f)
							sca = 1.0;

						rot -= 0.2f;
					}
					else
					{
						sca -= 0.1f;
						if (sca < 0.f)
						{
							sca = 0.f;
							SetState(GameLib::Actor::State::Dead);
						}

						rot += 0.1f;
					}

					SetScale(sca);
					SetRotation(rot);


					mCnt++;
				}

				Line::Line(StageScene* scene, const GameLib::Vector2& pos, bool isRight, int updateOrder)
					:StageActor(scene, pos, updateOrder)
				{



					mRect = new RectangleComponent(this, 800.f, 0.f, GameLib::Color::Black);
					if (isRight)
						mRect->SetAdjust(Vec2(400.f, 0.f));
					else
						mRect->SetAdjust(Vec2(-400.f, 0.f));

					for (int i = 0; i < 4; i++)
					{
						mBody[i] = new Body(this, "Beam", 200.f, 0.f);
						if (isRight)
							mBody[i]->SetAdjust(Vec2(-300.f + 200.f * i + 400.f, 0.f));
						else
							mBody[i]->SetAdjust(Vec2(-300.f + 200.f * i - 400.f, 0.f));
						mBody[i]->SetColor(GameLib::Vector3(0.f, 255.f, 0.f));
					}
				}

				Line::~Line()
				{
				}

				void Line::UpdateStageActor()
				{
	
					if (mCnt == 10)
					{
						float h = 40.f;
						mRect->SetHeight(h);
						for (int i = 0; i < 4; i++)
							mBody[i]->SetHeight(h);
					}
					else if (mCnt > 30)
					{
						float h = mRect->GetHeight();
						h -= 3.f;
						if (h < 0.f)
						{
							h = 0.f;
							SetState(GameLib::Actor::State::Dead);
						}
						mRect->SetHeight(h);
						for (int i = 0; i < 4; i++)
							mBody[i]->SetHeight(h);
					}
					mCnt++;
				}

			}

		}
	}
}
