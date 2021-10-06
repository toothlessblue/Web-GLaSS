#pragma once

// Forward declarations
class GameObject;

class Component {
public:
	GameObject* gameObject;

	Component();
	virtual void update();

	bool enabled = true;
private:

};

#include "../GameObject/GameObject.hpp"