#include <iostream>

//#include <glad/glad.h>
#include "../dependencies/glad/build/include/glad/glad.h"
//#include <GLFW/glfw3.h> 
#include "../dependencies/glfw/include/GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// settings
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(width, height, 0, 0);
    std::cout << "Viewport update -> width: " << width << " height: " << height << std::endl;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {

}

int main(int argc, char* argv[]) {

    // glfw: ininial configuration
    // ---------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: initializing window
    // -------------------------
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, argv[0], nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed generating window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell glfw to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// --------------------- 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed initializing OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // configure global opengl state 
    glEnable(GL_DEPTH_TEST);

    // application main loop
    while (!glfwWindowShouldClose(window)) {
        //render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved, etc)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate(); 

    return 0;
}
