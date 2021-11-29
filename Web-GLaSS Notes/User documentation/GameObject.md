More or less mimics unity GameObjects.

GameObjects contain a list of components

Contains a function `updateComponents` which is called once per frame, this calls `update` on every component in the list

`addComponent` adds a component to this list, and sets the components `gameObject` property to this GameObject

`createComponent<T>` creates a component of type `T`, and then calls `addComponent` using that component as an argument

Every GameObject contains a [[Transform]] component and a special property pointing to it.