#pragma once

// Forward declarations
class GameObject;

class Component {
public:
	GameObject* gameObject;

	Component();
	virtual void update();

	bool enabled = true;
	int componentId; // index in the component list of the gameobject this belongs to
private:
};

#include "../GameObject/GameObject.hpp"