#include"include/Draw/AnimComponent.hpp"
#include"include/Data.hpp"

#include<iostream>

namespace GameLib
{
	using Animation = std::vector<Texture*>;

	AnimComponent::AnimComponent(Actor* actor, int drawOrder, int updateOrder)
		:TextureComponent(actor, drawOrder, updateOrder)
		, mCurrFrame(0.0)
		, mAnimFPS(24.0)
		, mLoopMax(-1)
		, mLoopCnt(0)
		, mChannel(0)
	{
	}

	AnimComponent::AnimComponent(Actor* actor, std::vector<Animation>& animations, float fps, int drawOrder, int updateOrder)
		:AnimComponent(actor, drawOrder, updateOrder)
	{
		SetAnimation(animations);
		mAnimFPS = fps;
	}

	AnimComponent::AnimComponent(Actor* actor, Animation& animation, float fps, int drawOrder, int updateOrder)
		:AnimComponent(actor, drawOrder, updateOrder)
	{
		SetAnimation(animation);
		mAnimFPS = fps;
	}

	AnimComponent::~AnimComponent()
	{
	}

	void AnimComponent::Update()
	{
		if (mAnimations[mChannel].size() > 0)
		{
	
			if (mLoopMax == -1 || mLoopMax > mLoopCnt)
			{
				//現在のフレームを更新
				mCurrFrame += mAnimFPS / static_cast<double>(Data::GetFPS());
				
				//巻き戻し
				while (mCurrFrame >= mAnimations[mChannel].size())
				{
					mCurrFrame -= mAnimations[mChannel].size();
					mLoopCnt++;
					if (mLoopCnt == mLoopMax)
						mCurrFrame = mAnimations[mChannel].size() - 1;
				}
			}
			//現時点のテクスチャを設定する
			SetTexture(mAnimations[mChannel][static_cast<int>(mCurrFrame)]);
		}
	}

	void AnimComponent::SetAnimation(std::vector<Animation>& animations)
	{
		
		if (animations.size() > 0)
		{
			for (auto iter = animations.begin(); iter != animations.end(); iter++)
			{
				mAnimations.emplace_back(*iter);
			}
			SetTexture(mAnimations[mChannel][0]);
		}

	}

	void AnimComponent::SetAnimation(Animation& animation)
	{
		mAnimations.emplace_back(animation);
		SetTexture(mAnimations[mChannel][0]);
	}

	void AnimComponent::SetChannel(unsigned int c)
	{
	
		if (0 <= c && c <= mAnimations.size()) {
			if (mChannel != c) {
				mChannel = c;
				mCurrFrame = 0.0;
				mLoopCnt = 0;
			}
		}
	}
}