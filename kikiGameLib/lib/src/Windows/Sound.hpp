#pragma once
#include<string>
#include <dsound.h>

namespace GameLib
{

	class SoundManager
	{
	public: 
		SoundManager();
		~SoundManager();

		bool Init();
	};

	class Sound
	{
	public:
		Sound(LPDIRECTSOUNDBUFFER ptr);
		virtual ~Sound();

		LPDIRECTSOUNDBUFFER GetPtr() const { return mPtr; }

	private:
		LPDIRECTSOUNDBUFFER mPtr;
	};

	Sound* LoadSound(const std::string& fileName);

	Sound* CopySoundData(Sound* sound);

	void SoundPlay(Sound* sound, bool loop);
	void SoundStop(Sound* sound);
	void SetSoundVolume(Sound* sound,unsigned int vol);
}