#pragma once
#include<string>
#include<unordered_map>
#include<vector>

namespace GameLib
{
	class Texture;
	class Font;
	class Sound;

	class Data
	{
	private:
		Data() = default;
	public:
		virtual ~Data();

		static Texture* GetTexture(const std::string& fileName);
		static Font* GetFont(const std::string& fileName);
		static Sound* GetSound(const std::string& fileName);
		
		static float GetFPS() { return mFPS; }
		static float GetWindowWidth() { return mWindowWidth; }
		static float GetWindowHeight() { return mWindowHeight; }

	protected:
		static float mFPS;
		static float mWindowWidth;
		static float mWindowHeight;

		static std::unordered_map<std::string, Texture*> mTextures;
		static std::unordered_map<std::string, Font*> mFonts;
		static std::unordered_map<std::string, Sound*> mSounds;
	};
}