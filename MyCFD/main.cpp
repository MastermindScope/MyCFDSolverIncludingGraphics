//Problem at the moment: doesn't scale. probably pointer magic is wrong. maybe even just the stupid 
//bool "scalingDone" (don't think so tbh)
//
//
//
//
//


#include <GLFW/glfw3.h>
#include <iostream>
#include "glfwHandler.h"
#include "FileReader.h"
#include "CoordinateTransformer.h"


struct giveOver
{
    glfwHandler handler;
    FileReader* reader;
};


 void scrollCallback(GLFWwindow* window, double xoff, double yoff) {
    int sign = yoff / abs(yoff);
    glfwHandler callbackHandler = *(glfwHandler*)(glfwGetWindowUserPointer(window));



    /*Working Shit
    FileReader* boundSTL = (FileReader*)(glfwGetWindowUserPointer(window));


    std::cout << pow(1.1F, sign) << std::endl;


    boundSTL->coordinates = callbackHandler.scale(boundSTL->coordinates, boundSTL->storageSize, 0, pow(1.01, sign));
    

    */
    
    


}


int main(void)
{
    GLFWwindow* mainWindow = nullptr;
    const char* description;
    FileReader reader("C:\\Users\\Public\\heart.stl");
    glfwHandler handler;
    giveOver uebergabe;



    uebergabe.handler = handler;
    uebergabe.reader = &reader;


    FileReader* boundSTL = &reader; //using this for scroll scaling
    
    //BaseClass* boundPair[2] = {&handler, &reader}; //using this for clicking and dragging, glfw needs to know that MB is clicked
                                                  //but the callbackFun also needs the coordinates

    uintptr_t boundPair[2] = {(uintptr_t)&handler, (uintptr_t)&reader};

    glfwHandler* bindToWindow = &handler;

    handler.setScalingDone();
    

    if (handler.makeWindow() == 0) {
        std::cout << "Window creation failed!";
        return -1;
    }

    glfwSetWindowUserPointer(handler.handlerWindow, bindToWindow); //just give it boundSTL for shit to work
    std::cout << boundSTL << std::endl;
    std::cout << glfwGetWindowUserPointer(handler.handlerWindow) << std::endl;



    glfwSetScrollCallback(handler.handlerWindow, &scrollCallback);
    handler.scale(reader.coordinates, reader.storageSize);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(handler.handlerWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        std::cout << reader.coordinates[0].V1[0] << std::endl;

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





