#pragma once
#include"lib/include/Actor.hpp"
#include<string>

namespace GameLib
{
	class TextComponent;
	class Vector3;
	class Vector2;
}


namespace StageEditor
{
	class EditingScene;
	class EditingActor;

	class CommandActor : public GameLib::Actor
	{
	public:
		CommandActor(EditingScene* scene);
		virtual ~CommandActor();

		virtual void Input(const GameLib::InputState& state) override;
		virtual void Update() override;

		bool GetCheckFlag() const { return mCheckFlag; }
		bool GetSaveFlag() const { return mSaveFlag; }
		void SaveComplete() { mSaveFlag = false; }
		const std::string& GetText() const;
		bool GetLoadFlag() const { return mLoadFlag; }
		void LoadComplete() { mLoadFlag = false; }

	private:
		GameLib::TextComponent* mTextComponent;
		EditingActor* mNowEditingActor;
		EditingScene* mEditingScene;

		bool mCheckFlag;
		bool mSaveFlag;
		bool mLoadFlag;

		//EnterÇ∆ï∂éöóÒÇï]âø
		void EvaluateTextAndEnter(bool enter,const GameLib::Vector2& cursorPos);
	};

	//stateÇ©ÇÁstd::stringå^ÇÃì«Ç›èoÇµ
	std::string GetKey(const GameLib::InputState& state);

	
}