#pragma once
#include"lib/include/Component.hpp"
#include<string>

namespace GameLib
{
	class Sound;

	class SoundComponent : public Component
	{
	public:
		SoundComponent(Actor* actor,const std::string& fileName, int updateOrder = 0);
		virtual ~SoundComponent();

		void Play(bool loop = false);
		void Stop();
		//0-100
		void SetVolume(unsigned int vol);

	private:
		Sound* mSound;

		unsigned int mVolume;

	};

}