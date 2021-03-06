#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>

#include "Keyboard.h"
#include "Mouse.h"
#include "Draw.h"

class Window {
    private:
        GLFWwindow* window = NULL;
        GLFWmonitor* monitor = NULL;

    public:
        void init(const char* title, int width, int height, bool full_window);
        void mainLoop(int width, int height);
        void closeWindow(GLFWwindow* window);
        GLFWwindow* getInitializedWindow();
};

void Window::init(const char* title, int width, int height, bool full_window) {

    if (full_window) {
        monitor = glfwGetPrimaryMonitor();
    } 

    window = glfwCreateWindow(width, height, title, monitor, NULL);

    Keyboard keyboard;
    keyboard.initKeyboard(window);

    Mouse mouse;
    mouse.initMouse(window);

    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Error initializing window");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, NULL);

    Window::mainLoop(width, height);
}

void Window::mainLoop(int width, int height) {
    Draw draw;

    while(!glfwWindowShouldClose(window)) {
        draw.render(width, height);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow* Window::getInitializedWindow() {
    return window;
}
