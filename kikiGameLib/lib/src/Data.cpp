#include"lib/include/Data.hpp"
#include"Windows/Graphics.hpp"
#include"Windows/Sound.hpp"

namespace GameLib
{

	std::unordered_map<std::string, Texture*> Data::mTextures;
	std::unordered_map<std::string, Sound*> Data::mSounds;
	std::unordered_map<std::string, Font*> Data::mFonts;
	float Data::mFPS = 0.f;
	float Data::mWindowWidth = 0.f;
	float Data::mWindowHeight = 0.f;

	Data::~Data()
	{
		

	}

	
	Texture* Data::GetTexture(const std::string& fileName)
	{
		
		Texture* tex = nullptr;
		auto iter = mTextures.find(fileName);
		if (iter != mTextures.end()) {
			tex = iter->second;
		}
		else
		{
			tex = LoadTexture(fileName);
			if (tex)
				mTextures.emplace(fileName, tex);
		}

		return tex;

	}

	Font* Data::GetFont(const std::string& fileName)
	{
		Font* font = nullptr;
		auto iter = mFonts.find(fileName);
		if (iter != mFonts.end()) {
			font = iter->second;
		}
		else
		{
			font = LoadFont(fileName);
			if (font)
				mFonts.emplace(fileName, font);
		}

		return font;
	}

	Sound* Data::GetSound(const std::string& fileName)
	{
		Sound* sound = nullptr;
		auto iter = mSounds.find(fileName);
		if (iter != mSounds.end()) {
			sound = iter->second;
		}
		else
		{
			sound = LoadSound(fileName);
			if (sound)
				mSounds.emplace(fileName, sound);
		}

		return sound;
	}
	

}