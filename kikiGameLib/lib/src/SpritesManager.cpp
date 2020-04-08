#include"lib/src/SpritesManager.hpp"
#include"lib/include/Draw/SpriteComponent.hpp"

namespace GameLib
{
	SpritesManager::SpritesManager()
	{
	}

	SpritesManager::~SpritesManager()
	{
	
	}

	void SpritesManager::Add(SpriteComponent* sprite)
	{
		int myDrawOrder = sprite->GetDrawOrder();
		auto iter = mSprites.begin();
		for (;
			iter != mSprites.end();
			iter++) {
			if (myDrawOrder < (*iter)->GetDrawOrder()) {
				break;
			}
		}
		mSprites.insert(iter, sprite);
	}

	void SpritesManager::Remove(SpriteComponent* sprite)
	{
		auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
		mSprites.erase(iter);
	}
}