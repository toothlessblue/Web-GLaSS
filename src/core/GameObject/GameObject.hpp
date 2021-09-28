#pragma once

#include <list>

// Forward declarations
class Component;
class Transform;

class GameObject {
private:
	std::list<Component*> components;

public:
	Transform* transform;

	GameObject();
	~GameObject();
	void updateComponents();

	/**
	 * Adds a component to this gameObject, currently there isn't a clean way to undo this 
	 */
	void addComponent(Component* component);
	
	/**
	 * Instantiates a new component of type T, calls GameObject::addComponent with it, 
	 * and returns the new component
	 * 
	 * @param T The type of component to add
	 */
	template<class T> T* createComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T not derived from Component");

		T* newComponent = new T();
		this->addComponent(newComponent);

		return newComponent;
	}
};

#include "../Component/Component.hpp"
#include "../components/Transform/Transform.hpp"