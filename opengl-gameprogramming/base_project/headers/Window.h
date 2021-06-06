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
        void Init(const char* title, int width, int height, bool full_window);
        void MainLoop(int width, int height);
};

void Window::Init(const char* title, int width, int height, bool full_window) {

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

    Window::MainLoop(width, height);
}

void Window::MainLoop(int width, int height) {
    while(!glfwWindowShouldClose(window)) {
        Draw(width, height);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
