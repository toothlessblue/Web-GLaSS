#pragma once

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

// TODO *sigh*
//#include "../GameObject/GameObject.hpp"