#include <glm\glm.hpp>

class Input{
public:
	static glm::vec2* MouseClick(int button, int state, int x, int y);
	static void MouseMotion(glm::vec2* v, int x, int y);
	static void KeyboardPressed (unsigned char key, int x, int y);
	static void KeyboardSpecialPressed(int key, int x, int y);
};