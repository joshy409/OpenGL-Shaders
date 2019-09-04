#pragma once

class context {
private:

	
public:
	 struct GLFWwindow * window;
	bool init(int width, int height, const char * title);
	void tick();
	void term();
	void clear();

	bool shouldClose() const;
	void getWindow(GLFWwindow* newWin) { newWin = window; };
};