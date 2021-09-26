#pragma once

class GameObject;
class Component {
public:
	Component();
	virtual void update();
	GameObject* gameObject;
private:

};