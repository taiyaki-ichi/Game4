#pragma once
#include"Stage/StageActor.hpp"
#include<string>
#include<vector>

namespace GameLib
{
	class InputState;
	class TextureComponent;
	class Vector2;
	
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

	private:
		GameLib::TextureComponent* mTexture;
		Game::Stage::Body* mBody;

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
}