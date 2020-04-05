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
		//以下、ゲッターセッター
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
		//Actorの所属するScene
		Scene* mScene;

		State mState;

		ComponentsManager* mComponentsManager;

		//Actorの更新順序
		int mUpdateOrder;

		//座標関連
		//Actorの中心位置
		Vector2 mPosition;
		//Actorのスケール（1.0fが100%)
		float mScale;
		//回転の角度
		float mRotation;
	};
}