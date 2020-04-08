#include"lib/include/SoundComponent.hpp"
#include"Windows/Sound.hpp"
#include"lib/include/Data.hpp"

namespace GameLib
{



	SoundComponent::SoundComponent(Actor* actor, const std::string& fileName, int updateOrder)
		:Component(actor,updateOrder)
		,mVolume(50)
		,mSound(nullptr)
	{
		Sound* s = Data::GetSound(fileName);
		if (s)
		{
			mSound = CopySoundData(s);
			SetSoundVolume(mSound, mVolume);
		}

	}

	SoundComponent::~SoundComponent()
	{
		if (mSound)
			delete mSound;
	}

	void SoundComponent::Play(bool loop)
	{
		SoundPlay(mSound, loop);
	}

	void SoundComponent::Stop()
	{
		SoundStop(mSound);
	}

	void SoundComponent::SetVolume(unsigned int vol)
	{
		mVolume = vol;
		SetVolume(vol);
	}

}