#pragma once
#include<vector>

namespace GameLib
{
	class SpriteComponent;

	class SpritesManager
	{
	public:
		SpritesManager();
		~SpritesManager();

		void Add(SpriteComponent* sprite);
		void Remove(SpriteComponent* sprite);

		std::vector<SpriteComponent*>& GetSprites() { return mSprites; }

	private:
		std::vector<SpriteComponent*> mSprites;

	};
}