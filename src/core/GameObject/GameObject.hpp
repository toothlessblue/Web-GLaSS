#pragma once
#include <vector>
#include "../Component/Component.hpp"
#include "../Time/Time.hpp"
#include "../Input/Input.hpp"
#include "../components/RectTransform/RectTransform.hpp"

// Forward declarations
class Component;
class Transform;
class RectTransform;

class GameObject {
private:
	std::vector<Component*> components;
	
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

	RectTransform* useRectTransform();
};

#include "../Component/Component.hpp"
#include "../components/Transform/Transform.hpp"