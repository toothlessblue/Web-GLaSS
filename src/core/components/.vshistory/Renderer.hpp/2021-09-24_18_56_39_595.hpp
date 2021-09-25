#include <GL/glew.h>
#include "../Component.hpp"

class Renderer : public Component {
public:
	Renderer() {

	}

	virtual void render() {
		std::cout << "Renderer rendered\n";
	}
private:

};