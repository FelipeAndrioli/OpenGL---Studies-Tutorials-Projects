#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {

    //Initialize glfw
    glfwInit();

    //Set the glfw version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //With core-profile we'll get access to a smaller subset of OpenGL features without 
    //backwards-compatible features we no longer need
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //The following line is only needed in Mac OS X
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create a window object
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Make the context of our window the main context on the current thread
    glfwMakeContextCurrent(window);

    //GLAD manages function pointers for OpenGL, so we want to initialize GLAD before we call any 
    //OpenGL function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //To tell OpenGL the size of the rendering window so OpenGL know how we want to display the data
    //and coordinates with respect to the window, we use the function glViewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //In the moment the user resizes the window, the viewport should be adjusted as well. We can 
    //register a callback function on the window that gets called each time the window is resized.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Render loop
    while (!glfwWindowShouldClose(window)) {
        //glfwSwapBuffers will swap the color buffer that is used to render to during this render 
        //iteration and show it as output to the screen
        glfwSwapBuffers(window);

        //glfwPollEvents checks if any events are triggered (like keyboard input or mouse movement 
        //events), updates the window state, and calls the corresponding functions (which we can 
        //register via callback methods)
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
