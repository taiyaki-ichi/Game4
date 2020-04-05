#pragma once
#include<memory>

namespace GameLib
{
	class InputState;
	class ActorsManager;
	class SpritesManager;
	class InputState;
	class Data;
	class Actor;
	namespace MySDL
	{
		struct Handlers;
	}

	class Scene
	{
	public:

		Scene();
		virtual ~Scene();

		//�p�������V�[���Ǝ��̏������s��
		virtual void Input(const InputState& state);
		virtual Scene* Update();

		void AddActor(Actor* actor);
		void RemoveActor(Actor* actor);
		ActorsManager* GetActorsManagerPtr() const;
		SpritesManager* GetSpritesManagerPtr() const;


	private:

		ActorsManager* mActorsManagerPtr;
		SpritesManager* mSpritesManagerPtr;

	};
}