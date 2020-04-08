#pragma once
#include"lib/include/Data.hpp"


namespace GameLib
{

	class DataImpl : public Data
	{
	private:
		DataImpl() = default;
	public:
		~DataImpl() = default;

		static void SetFPS(float fps)
		{
			Data::mFPS = fps;
		}

		static void SetWindowWidth(float w)
		{
			Data::mWindowWidth = w;
		}

		static void SetWindowHeight(float h)
		{
			Data::mWindowHeight = h;
		}

		static void Unload()
		{
			for (auto i : Data::mTextures) {
				delete i.second;
			}
			Data::mTextures.clear();

			for (auto i : Data::mFonts) {
				delete i.second;
			}
			Data::mFonts.clear();
		}
	};
}