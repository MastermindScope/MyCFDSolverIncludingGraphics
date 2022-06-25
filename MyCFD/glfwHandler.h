#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include "BaseClass.h"
#include "FileReader.h"

class glfwHandler : public BaseClass
{
public:
	//constructor
	glfwHandler() { 
		std::cout << "glfwHandler created" << std::endl; 
		handlerWindow = nullptr;
	}



	//public functions
	bool makeWindow();
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	void drawFromArray(triangle* readArray, int size);
	triangle* scale(triangle* readArray, int size, bool initial = 1, float factor = 1);
	void setScalingDone() { scalingDone = 0; };
	triangle* shift(triangle* readArray, int size, float xshift, float yshift);
	triangle* rotate(triangle* readArray, int size, float xrotate, float yrotate);



	//public variables
	GLFWwindow* handlerWindow;
	bool scalingDone = 1;
	bool LMBDown = 0;
	float xprevious = 0;
	float yprevious = 0;
	

private:

	void sortEntries(triangle* readArray, int size);
	
	



	






};




