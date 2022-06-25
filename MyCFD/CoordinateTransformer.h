#pragma once
#include "BaseClass.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include "FileReader.h"


class CoordinateTransformer : public BaseClass
{
public:
	void bindSTL(FileReader* File);



	//void scrollCallback(GLFWwindow* window, double xoff, double yoff);







private:

	FileReader* boundSTL;





};

