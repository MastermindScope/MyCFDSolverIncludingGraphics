#include "glfwHandler.h"



bool glfwHandler::makeWindow() {
    //this makes a new window and sets it as the current context


    /* Initialize the library */
    if (!glfwInit())
        return 0;

    /* Create a windowed mode window and its OpenGL context */
    handlerWindow = glfwCreateWindow(1500, 1000, "Hello World", NULL, NULL);
    if (!handlerWindow)
    {
        glfwTerminate();
        return 0;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(handlerWindow);


    return 1;

}



void glfwHandler::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void glfwHandler::drawFromArray(triangle* readArray, int size) {

    //std::cout << std::endl << readArray[0].V1[0] << std::endl;
    if (scalingDone == 0) {
        scale(readArray, size);
        scalingDone = 1;
        std::cout << "normalized" << std::endl;
    }
    //std::cout << std::endl << readArray[0].V1[0] << std::endl << std::endl;


    for (int k = 0; k < size; k++) {
        drawTriangle(readArray[k].V1[0], readArray[k].V1[1], readArray[k].V2[0]
            , readArray[k].V2[1], readArray[k].V3[0], readArray[k].V3[1]);
    }

}

BaseClass::triangle* glfwHandler::scale(triangle* readArray, int size, bool initial, float factor) {
    float max = 0;
    

    //search max of x and y
    if (initial == true) {
        for (int i = 0; i < size; i++) {
            if (abs(readArray[i].V1[0]) > max) {
                max = abs(readArray[i].V1[0]);
            }
            if (abs(readArray[i].V2[0]) > max) {
                max = abs(readArray[i].V2[0]);
            }
            if (abs(readArray[i].V1[1]) > max) {
                max = abs(readArray[i].V1[1]);
            }
            if (abs(readArray[i].V2[1]) > max) {
                max = abs(readArray[i].V2[1]);
            }
        }
    }
    

    //scale everything here

    if ((factor == 1) || (max != 0)) { factor = 1/max; }



    for (int i = 0; i < size; i++) {
        for (int k = 0; k < 3; k++) {
            readArray[i].V1[k] = readArray[i].V1[k] * factor;
            readArray[i].V2[k] = readArray[i].V2[k] * factor;
            readArray[i].V3[k] = readArray[i].V3[k] * factor;
        }
    }


    return readArray;


}

