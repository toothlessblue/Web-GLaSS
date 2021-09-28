#pragma once

// Forward declarations
class GameObject;

class Component {
public:
	GameObject* gameObject;

	Component();
	virtual void update();
private:

};

#include "../GameObject/GameObject.hpp"