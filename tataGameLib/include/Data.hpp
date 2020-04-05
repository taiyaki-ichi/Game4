#pragma once
#pragma once
#include<string>
#include<unordered_map>
#include<vector>

namespace GameLib
{
	class Texture;
	using Animation = std::vector<Texture*>;


	class Data
	{
	private:
		Data() = default;
	public:
		virtual ~Data();

		static Texture* GetTexture(const std::string& fileName);
		

		static float GetFPS() { return mFPS; }
		static float GetWindowWidth() { return mWindowWidth; }
		static float GetWindowHeight() { return mWindowHeight; }

	protected:
		static float mFPS;
		static float mWindowWidth;
		static float mWindowHeight;

		static std::unordered_map<std::string, Texture*> mTextures;
	};
}