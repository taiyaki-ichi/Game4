#pragma once
#include"Math.hpp"
#include<vector>

namespace GameLib
{
	class ComponentsManager;
	class InputState;
	class Scene;


	class Actor
	{
	public:
		enum class State
		{
			Active,
			Paused,
			Dead
		};

		Actor(Scene* scene, int updateOrder = 0);
		virtual ~Actor();

		virtual void Input(const InputState& state);
		virtual void Update();

		//
		//�ȉ��A�Q�b�^�[�Z�b�^�[
		//

		State GetState() const { return mState; }
		void SetState(State s) { mState = s; }
		const Vector2& GetPosition() const { return mPosition; }
		void SetPosition(const Vector2& pos) { mPosition = pos; }
		float GetScale() const { return mScale; }
		void SetScale(float scale) { mScale = scale; }
		float GetRotation() const { return mRotation; }
		void SetRotation(float rotation) { mRotation = rotation; }
		int GetUpdateOrder() const { return mUpdateOrder; }
		class Scene* GetScene() { return mScene; }
		ComponentsManager* GetComponentsManager() const { return mComponentsManager; }

	private:
		//Actor�̏�������Scene
		Scene* mScene;

		State mState;

		ComponentsManager* mComponentsManager;

		//Actor�̍X�V����
		int mUpdateOrder;

		//���W�֘A
		//Actor�̒��S�ʒu
		Vector2 mPosition;
		//Actor�̃X�P�[���i1.0f��100%)
		float mScale;
		//��]�̊p�x
		float mRotation;
	};
}