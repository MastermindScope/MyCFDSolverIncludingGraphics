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


BaseClass::triangle* glfwHandler::shift(triangle* readArray, int size, float xshift, float yshift) {
    for (int i = 0; i < size; i++) {
        readArray[i].V1[0] += xshift;
        readArray[i].V1[1] += yshift;
        readArray[i].V2[0] += xshift;
        readArray[i].V2[1] += yshift;
        readArray[i].V3[0] += xshift;
        readArray[i].V3[1] += yshift;
    }

    return readArray;
}


BaseClass::triangle* glfwHandler::rotate(triangle* readArray, int size, float xrotate, float yrotate) {
    //rotate around x-axis and y axis
    for (int i = 0; i < size; i++) {
        float xintermediate[4] = {readArray[i].V1[0], readArray[i].V2[0], readArray[i].V3[0], readArray[i].normal[0]};
        float yintermediate[4] = {readArray[i].V1[1], readArray[i].V2[1], readArray[i].V3[1], readArray[i].normal[1]};
        float zintermediate[4] = {readArray[i].V1[2], readArray[i].V2[2], readArray[i].V3[2], readArray[i].normal[2]};

        //V1 rotation
        readArray[i].V1[0] =  xintermediate[0] * cosf(yrotate) + zintermediate[0] * sinf(yrotate);
        readArray[i].V1[1] =  xintermediate[0] * sinf(yrotate) * sinf(xrotate) + yintermediate[0] * cosf(xrotate) - zintermediate[0] * sinf(xrotate) * cosf(yrotate);
        readArray[i].V1[2] = -xintermediate[0] * sinf(yrotate) * cosf(xrotate) + yintermediate[0] * sinf(xrotate) + zintermediate[0] * cosf(xrotate) * cosf(yrotate);

        //V2 rotation
        readArray[i].V2[0] =  xintermediate[1] * cosf(yrotate) + zintermediate[1] * sinf(yrotate);
        readArray[i].V2[1] =  xintermediate[1] * sinf(yrotate) * sinf(xrotate) + yintermediate[1] * cosf(xrotate) - zintermediate[1] * sinf(xrotate) * cosf(yrotate);
        readArray[i].V2[2] = -xintermediate[1] * sinf(yrotate) * cosf(xrotate) + yintermediate[1] * sinf(xrotate) + zintermediate[1] * cosf(xrotate) * cosf(yrotate);
        
        //V3 rotation
        readArray[i].V3[0] =  xintermediate[2] * cosf(yrotate) + zintermediate[2] * sinf(yrotate);
        readArray[i].V3[1] =  xintermediate[2] * sinf(yrotate) * sinf(xrotate) + yintermediate[2] * cosf(xrotate) - zintermediate[2] * sinf(xrotate) * cosf(yrotate);
        readArray[i].V3[2] = -xintermediate[2] * sinf(yrotate) * cosf(xrotate) + yintermediate[2] * sinf(xrotate) + zintermediate[2] * cosf(xrotate) * cosf(yrotate);

        //normal rotation
        readArray[i].normal[0] =  xintermediate[3] * cosf(yrotate) + zintermediate[3] * sinf(yrotate);
        readArray[i].normal[1] =  xintermediate[3] * sinf(yrotate) * sinf(xrotate) + yintermediate[3] * cosf(xrotate) - zintermediate[3] * sinf(xrotate) * cosf(yrotate);
        readArray[i].normal[2] = -xintermediate[3] * sinf(yrotate) * cosf(xrotate) + yintermediate[3] * sinf(xrotate) + zintermediate[3] * cosf(xrotate) * cosf(yrotate);

    }

    return readArray;
}



void glfwHandler::sortEntries(triangle* readArray, int size) {

}