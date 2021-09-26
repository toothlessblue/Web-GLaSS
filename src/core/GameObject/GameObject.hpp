#pragma once

#include <list>
#include "../Component/Component.hpp"
#include "../components/Transform/Transform.hpp"

class GameObject {
private:
	std::list<Component*> components;

public:
	GameObject();
	void updateComponents();
	void addComponent(Component* component);

	Transform* transform;
};