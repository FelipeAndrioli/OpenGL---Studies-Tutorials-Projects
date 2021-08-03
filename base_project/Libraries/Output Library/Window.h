#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>

class Window {
    private:
        GLFWwindow* window = NULL;
        GLFWmonitor* monitor = NULL;

    public:
        void init(const char* title, int width, int height, bool full_window);
        void mainLoop(int width, int height);
        void closeWindow(GLFWwindow* window);
        GLFWwindow* getInitializedWindow();
        GLFWwindow* getWindow();
};

void Window::init(const char* title, int width, int height, bool full_window) {

    if (full_window) {
        monitor = glfwGetPrimaryMonitor();
    } 

    window = glfwCreateWindow(width, height, title, monitor, NULL);

    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Error initializing window");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, NULL);

    //Window::mainLoop(width, height);
}

void Window::mainLoop(int width, int height) {

    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow* Window::getInitializedWindow() {
    return window;
}

GLFWwindow* Window::getWindow() {
    return window;
}
