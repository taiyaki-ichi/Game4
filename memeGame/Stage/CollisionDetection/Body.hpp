#pragma once
#include"include/Draw/SpriteComponent.hpp"
#include<string>


namespace Game
{
	namespace Stage
	{
		class StageActor;
		class LinerObject;

		class Body : public GameLib::SpriteComponent
		{
		public:
			using Vec2 = GameLib::Vector2;

			Body(StageActor* actor, const std::string& bodyName, int updateOrder = 0);
			Body(StageActor* actor, const std::string& bodyName, float width, float height, int updateOrder = 0);
			Body(StageActor* actor, const std::string& bodyName, float width, float height, const Vec2& adust, int updateOrder = 0);
			virtual ~Body();

			void Update() override;
			//�����`�̕`�ʂ̍ێg�p
			void Draw() override;

			static bool DrawFlag;

			//
			//�ȉ��A�Q�b�^�w�b�_
			//

			void SetWidth(float w) { mWidth = w; }
			void SetHeight(float h) { mHeight = h; }
			void SetWidthAndHeight(float w, float h) { mWidth = w; mHeight = h; }
			float GetWidth() const;
			float GetHeight() const;

			float GetRotatedWidth();
			float GetRotatedHeight();

			void SetAdjust(const Vec2& adjust) { mAdjust = adjust; };
			const Vec2& GetAdjust() const;

			void SetColor(const GameLib::Vector3& color) { mColor = color; }

			StageActor* GetStageOwner() const { return mStageOwner; }

			const std::string& GetName() const { return mName; }

		private:
			float mWidth;
			float mHeight;

			//�����p�̃x�N�g��
			Vec2 mAdjust;

			//���ʗp�̖��O
			std::string mName;

			StageActor* mStageOwner;

			//�����`�̐F
			GameLib::Vector3 mColor;

			//�S���ؓo�^�p
			LinerObject* mLinerObject;
		};


	}
}

