[Reference](https://en.cppreference.com/w/cpp/container/list)

```cpp
#include <list>

// Initialising a list
std::list<int> list = {1,2,3,4}; // Initialises a prepopulated list of integers
std::list<int> list = {}; // Initialises empty list

// Add values to a list
list.push_front
list.push_back

list.insert(value, index)

// Removes values from a list
list.pop_front
list.pop_back
list.clear


// Loop throug a list
for (int i : list) {
	// ...
}
```

- The FRONT of the list is the BEGINNING, i.e. index 0
- The BACK of the list is the END