//Problem at the moment: doesn't scale. probably pointer magic is wrong. maybe even just the stupid 
//bool "scalingDone" (don't think so tbh)
//
//
//
//
//
#define _USE_MATH_DEFINES

#include <GLFW/glfw3.h>
#include <iostream>
#include "glfwHandler.h"
#include "FileReader.h"
#include "CoordinateTransformer.h"
#include <cmath>


struct giveOver
{
    glfwHandler handler;
    FileReader* reader;
};


 void scrollCallback(GLFWwindow* window, double xoff, double yoff) {
    int sign = yoff / abs(yoff);
    glfwHandler callbackHandler = *(glfwHandler*)(glfwGetWindowUserPointer(window));
    
    FileReader* boundSTL = (*(giveOver*)(glfwGetWindowUserPointer(window))).reader;

    boundSTL->coordinates = callbackHandler.scale(boundSTL->coordinates, boundSTL->storageSize, 0, pow(1.1, sign));

}

 void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
     glfwHandler callbackHandler = (*(giveOver*)(glfwGetWindowUserPointer(window))).handler;

     if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
         callbackHandler.LMBDown = 1;
     }
     else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
         callbackHandler.LMBDown = 0;
     }

     std::cout << callbackHandler.LMBDown << std::endl;
 }

 void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
     glfwHandler callbackHandler = (*(giveOver*)(glfwGetWindowUserPointer(window))).handler;
     FileReader* boundSTL = (*(giveOver*)(glfwGetWindowUserPointer(window))).reader;

     int width, height;

     glfwGetWindowSize(window, &width, &height);
     
     
     int LMB = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
     int RMB = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

     //shifting the STL
     if (LMB == GLFW_PRESS) {
         float xshift = (xpos - callbackHandler.xprevious) / width;
         float yshift = (ypos - callbackHandler.yprevious) / height;
         callbackHandler.shift(boundSTL->coordinates, boundSTL->storageSize, xshift, -yshift);
     }

     

     //rotatinng the STL

     if (RMB == GLFW_PRESS) {
         float xangle = (xpos - callbackHandler.xprevious) / width * M_PI;
         float yangle = (ypos - callbackHandler.yprevious) / height * M_PI;

         callbackHandler.rotate(boundSTL->coordinates, boundSTL->storageSize, yangle, xangle);

     }




     (*(giveOver*)(glfwGetWindowUserPointer(window))).handler.xprevious = xpos;
     (*(giveOver*)(glfwGetWindowUserPointer(window))).handler.yprevious = ypos;
 }


int main(void)
{
    GLFWwindow* mainWindow = nullptr;
    const char* description;
    FileReader reader("C:\\Users\\Public\\wirbelKammer.stl");
    glfwHandler handler;
    giveOver uebergabe;



    uebergabe.handler = handler;
    uebergabe.reader = &reader;


    handler.setScalingDone();
    

    if (handler.makeWindow() == 0) {
        std::cout << "Window creation failed!";
        return -1;
    }

    glfwSetWindowUserPointer(handler.handlerWindow, &uebergabe);



    glfwSetScrollCallback(handler.handlerWindow, &scrollCallback);
    glfwSetMouseButtonCallback(handler.handlerWindow, &mouseButtonCallback);
    glfwSetCursorPosCallback(handler.handlerWindow, &cursorPositionCallback);



    handler.scale(reader.coordinates, reader.storageSize);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(handler.handlerWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        handler.drawFromArray(reader.coordinates, reader.storageSize);
        

        

        /* Swap front and back buffers */
        glfwSwapBuffers(handler.handlerWindow);
        
        /*wait for event to happen*/
        glfwWaitEvents();

        /* Poll for and process events */
        glfwPollEvents();
    }

    std::cout << glfwGetError(&description);

    
    

    glfwTerminate();
    return 0;
}





