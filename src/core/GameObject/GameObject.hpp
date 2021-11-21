#pragma once
#include <vector>
#include "../Time/Time.hpp"
#include "../Input/Input.hpp"

// Forward declarations
class Component;
class Transform;
class RectTransform;

class GameObject {
public:
	Transform* transform;

	GameObject();
	~GameObject();
	void updateComponents();
	void startComponents();

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

	void setActive(bool value);
	bool isActive();
private:
	std::vector<Component*> components;
	bool enabled = true;

	unsigned int frameCheckedActivity = 0;
	bool cachedIsActive = true;
};

#include "../components/Transform/Transform.hpp"
#include "../Component/Component.hpp"
#include "../components/RectTransform/RectTransform.hpp"