#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/*
    Steps to create a simple program

    - Initialize library
    - Initialize the window
    - Verify the initialization of the window
    - Create a loop until the user closes the window
    - Inside the loop some configurations need to be done
        - glClear
        - glfwSwapBuffers
        - glfwPollEvents
        - The things we want to render should come after the glClear and before glfwSwapBuffers

*/

int main(int argc, char** argv) {

    GLFWwindow*  window;

    if (!glfwInit()) {
        std::cout << "The application have failed in initialize the library..." << std::endl;
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Triangle.exe", NULL, NULL);

    if (!window) {
        std::cout << "The application have failed in initialize the window..." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLfloat vertices[] = {
        0, 0.5, 0.0, //top corner
        -0.5, -0.5, 0.0,  //bottom left corner
        0.5, -0.5, 0.0 //bottom right corner
    };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_CLEAR_BUFFER);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_VERTEX_ARRAY);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}