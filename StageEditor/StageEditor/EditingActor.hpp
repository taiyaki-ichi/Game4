#pragma once
#include"Stage/StageActor.hpp"
#include<string>
#include<vector>

namespace GameLib
{
	class InputState;
	class TextureComponent;
	class Vector2;
	class LineComponent;
	class CircleLineComponent;
	
}
namespace Game
{
	namespace Stage
	{
		class Body;
		class RectangleComponent;
	}
}

namespace StageEditor
{
	class EditingScene;

	using Vec2 = GameLib::Vector2;

	class EditingActor : public Game::Stage::StageActor
	{
	public:
		EditingActor(EditingScene* scene,const Vec2& pos,const std::string& name,int dataNum);
		virtual ~EditingActor();

		virtual void Input(const GameLib::InputState& state) override;
		virtual void UpdateStageActor() override;

		void SetName(const std::string& name) { mName = name; }
		const std::string& GetName() const { return mName; }
		void AddData(double d) { mDates.emplace_back(d); }
		std::vector<double>& GetDatas() { return mDates; }

		int GetDataNum() const { return mDataNum; }
		bool IsOk() { return mDataNum <= mDates.size(); }

		virtual void AdjustPosSub(const Vec2& vec) override;

		EditingScene* GetEditingScene() const { return mEditingScene; }

	private:
		std::string mName;
		std::vector<double> mDates;
		EditingScene* mEditingScene;
		
		int mDataNum;
		bool mClicked;
	};

	class EditingPlayer : public EditingActor
	{
	public:
		EditingPlayer(EditingScene* scene, const Vec2& pos);
		virtual ~EditingPlayer();

		static int GetNum() { return mNum; }

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;

		static int mNum;

	};

	class EditingGround : public EditingActor
	{
	public:
		EditingGround(EditingScene* scene, const Vec2& pos);
		virtual ~EditingGround();

		virtual void UpdateStageActor() override;

	private:
		Game::Stage::RectangleComponent* mRect;
		Game::Stage::Body* mBody;

	};

	class EditingTriple : public EditingActor
	{
	public:
		EditingTriple(EditingScene* scene, const Vec2& pos);
		virtual ~EditingTriple();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;

	};

	class EditingToge : public EditingActor
	{
	public:
		EditingToge(EditingScene* scene, const Vec2& pos);
		virtual ~EditingToge();


	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingFrog : public EditingActor
	{
	public:
		EditingFrog(EditingScene* scene, const Vec2& pos);
		virtual ~EditingFrog();

		virtual void UpdateStageActor() override ;

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;

		GameLib::LineComponent* mLine;
	};

	class EditingStraightBee : public EditingActor
	{
	public:
		EditingStraightBee(EditingScene* scene, const Vec2& pos);
		virtual ~EditingStraightBee();

		virtual void UpdateStageActor() override;

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;

		GameLib::LineComponent* mLine;

	};

	class EditingCircleBee : public EditingActor
	{
	public:
		EditingCircleBee(EditingScene* scene, const Vec2& pos);
		virtual ~EditingCircleBee();

		virtual void UpdateStageActor() override;

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;

		GameLib::LineComponent* mLine1;
		GameLib::CircleLineComponent* mCircle;
	};

	class EditingItemCock : public EditingActor
	{
	public:
		EditingItemCock(EditingScene* scene, const Vec2& pos);
		virtual ~EditingItemCock();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingItemWizard : public EditingActor
	{
	public:
		EditingItemWizard(EditingScene* scene, const Vec2& pos);
		virtual ~EditingItemWizard();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingItemAlien : public EditingActor
	{
	public:
		EditingItemAlien(EditingScene* scene, const Vec2& pos);
		virtual ~EditingItemAlien();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingContainer : public EditingActor
	{
	public:
		EditingContainer(EditingScene* scene, const Vec2& pos);
		virtual ~EditingContainer();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingMoveGround : public EditingActor
	{
	public:
		EditingMoveGround(EditingScene* scene,const Vec2& pos);
		virtual ~EditingMoveGround();

		virtual void UpdateStageActor() override;

	private:
		Game::Stage::Body* mBody;
		GameLib::LineComponent* mLine;
		Game::Stage::RectangleComponent* mRect;
	};

	class EditingDiamond : public EditingActor
	{
	public:
		EditingDiamond(EditingScene* scene, const Vec2& pos);
		virtual ~EditingDiamond();

		static int GetNum() { return mNum; }

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;

		static int mNum;
	};

	class EditingStandLight : public EditingActor
	{
	public:
		EditingStandLight(EditingScene* scene, const Vec2& pos);
		virtual ~EditingStandLight();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingCarrot : public EditingActor
	{
	public:
		EditingCarrot(EditingScene* scene, const Vec2& pos);
		virtual ~EditingCarrot();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingDogu : public EditingActor
	{
	public:
		EditingDogu(EditingScene* scene, const Vec2& pos);
		virtual ~EditingDogu();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingHeart : public EditingActor
	{
	public:
		EditingHeart(EditingScene* scene, const Vec2& pos);
		virtual ~EditingHeart();

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;
	};

	class EditingWarp : public EditingActor
	{
	public:
		EditingWarp(EditingScene* scene, const Vec2& pos);
		virtual ~EditingWarp();

		virtual void UpdateStageActor() override;

	private:
		GameLib::TextureComponent* mTexture;
		GameLib::TextureComponent* mTexture2;
		Game::Stage::Body* mBody;
		Game::Stage::Body* mBody2;

	};

	class EditingGoal : public EditingActor
	{
	public:
		EditingGoal(EditingScene* scene, const Vec2& pos);
		virtual ~EditingGoal();
	};

	class EditingMaimai : public EditingActor
	{
	public:
		EditingMaimai(EditingScene* scene, const Vec2& pos);
		virtual ~EditingMaimai();
	};

	class EditingMissile : public EditingActor
	{
	public:
		EditingMissile(EditingScene* scene, const Vec2& pos);
		virtual ~EditingMissile() {}
	};

	class EditingTear : public EditingActor
	{
	public:
		EditingTear(EditingScene* scene, const Vec2& pos);
		virtual ~EditingTear();

		static int GetNum() { return mNum; }

	private:
		static int mNum;
	};

	class EditingBottom : public EditingActor
	{
	public:
		EditingBottom(EditingScene* scene, const Vec2& pos);
		virtual ~EditingBottom();

		virtual void UpdateStageActor() override;

	private:
		GameLib::LineComponent* mLine;
	};
}