#include"include/ComponentsManager.hpp"
#include"include/Component.hpp"

namespace GameLib
{
	ComponentsManager::ComponentsManager()
	{
	}
	ComponentsManager::~ComponentsManager()
	{
		while (!mComponents.empty())
		{
			delete mComponents.back();
		}
	}

	void ComponentsManager::Add(Component* comp)
	{
		int myOrder = comp->GetUpdateOrder();
		auto iter = mComponents.begin();
		for (;
			iter != mComponents.end();
			iter++) {
			if (myOrder < (*iter)->GetUpdateOrder()) {
				break;
			}
		}
		mComponents.insert(iter, comp);
	}

	void ComponentsManager::Remove(Component* comp)
	{
		auto iter = std::find(mComponents.begin(), mComponents.end(), comp);
		if (iter != mComponents.end()) {
			mComponents.erase(iter);
		}
	}
}