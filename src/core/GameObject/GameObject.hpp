#pragma once

#include "../components/Transform/Transform.hpp"
#include <list>

class GameObject {
private:
	std::list<Component*> components;

public:
	GameObject();
	void updateComponents();
	void addComponent(Component* component);

	Transform* transform;
};