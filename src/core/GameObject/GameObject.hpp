#pragma once

#include <list>

class Component;
class Transform;

class GameObject {
private:
	std::list<Component*> components;

public:
	GameObject();
	void updateComponents();
	void addComponent(Component* component);

	Transform* transform;
};

#include "../Component/Component.hpp"
#include "../components/Transform/Transform.hpp"