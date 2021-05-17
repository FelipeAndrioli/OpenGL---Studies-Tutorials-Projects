#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char** argv) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    int screenWidth;
    int screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*
        Specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    */
    glViewport(0.0f, 0.0f, screenWidth, screenHeight);

    /*
        Projection matrix defines the properties of the camera that views the objects in the world coordinate frame. 
        Here you typically set the zoom factor, aspect ration and the near and far clipping planes
    */
    glMatrixMode(GL_PROJECTION);

    /*
        Replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as 
        glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    */
    glLoadIdentity();

    /*
        Essentially set coordinate system
    */
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);

    /*
        (Default matrix mode) Modelview matrix defines how your objects are transformed (meaning translation, rotation 
        and scaling) in your world
    */
    glMatrixMode(GL_MODELVIEW);

    /*
        Same as the above
    */
    glLoadIdentity();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
