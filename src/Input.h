class Input{
public:
	static void MouseClick(int button, int state, int x, int y);
	static void KeyboardPressed (unsigned char key, int x, int y);
	static void KeyboardSpecialPressed(int key, int x, int y);
	void leftClick(int x, int y);
	void rightClick(int x, int y);
};