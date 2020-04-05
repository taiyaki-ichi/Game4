#pragma once
#include"TextureComponent.hpp"
#include<vector>

namespace GameLib
{
	using Animation = std::vector<Texture*>;

	class AnimComponent : public TextureComponent
	{
	public:
		AnimComponent(Actor* actor, int drawOrder = 0, int updateOrder = 0);
		AnimComponent(Actor* actor, std::vector<Animation>& animations, float fps = 24.f, int drawOrder = 0, int updateOrder = 0);
		AnimComponent(Actor* actor, Animation& animation, float fps = 24.f, int drawOrder = 0, int updateOrder = 0);
		virtual ~AnimComponent();

		virtual void Update() override;

		void SetAnimation(std::vector<Animation>& animations);
		void SetAnimation(Animation& animation);

		void SetChannel(unsigned int c);

		void SetAnimFPS(double fps) { mAnimFPS = fps; }

	private:
		std::vector<Animation> mAnimations;

	protected:
		double mCurrFrame;
		double mAnimFPS;

		//デフォで-1,無限ループ
		int mLoopMax;
		int mLoopCnt;

		unsigned int mChannel;

	};
}