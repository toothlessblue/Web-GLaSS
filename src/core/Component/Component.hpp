#pragma once

// Forward declarations
class GameObject;

class Component {
public:
	GameObject* gameObject;

	Component(); // gameObject unavailable in constructor
	virtual void start();
	virtual void update();

	bool isActive();
	void setActive(bool value);

	int componentId; // index in the component list of the gameobject this belongs to
private:
	bool enabled = true;
};

// #include "../GameObject/GameObject.hpp"
// TODO figure out why this include breaks the build
