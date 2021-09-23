#include "Transform.hpp"
#include "Component.hpp"
#include <list>

class GameObject {
private:
	std::list<Component> components;

public:
	GameObject() {

	}

	void updateComponents() {
		for (Component const& component : this.components) {
			component.update();
		}
	}

	void addComponent(Component* component) {
		this->components.push_back(component);
	}
};