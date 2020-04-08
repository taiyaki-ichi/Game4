#pragma once
#include<vector>

namespace GameLib
{
	class Component;

	class ComponentsManager
	{
	public:
		ComponentsManager();
		~ComponentsManager();

		void Add(Component* comp);
		void Remove(Component* comp);

		std::vector<Component*>& GetComponents() { return mComponents; }

	private:
		std::vector<Component*> mComponents;
	};
}