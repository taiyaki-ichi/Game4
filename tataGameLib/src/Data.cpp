#include"include/Data.hpp"
#include"Windows/Graphics.hpp"

namespace GameLib
{

	std::unordered_map<std::string, Texture*> Data::mTextures;
	//std::unordered_map<std::string, Music*> Data::mMusics;
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
	

}