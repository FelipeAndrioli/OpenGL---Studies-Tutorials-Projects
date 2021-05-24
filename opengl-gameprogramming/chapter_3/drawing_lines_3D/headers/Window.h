#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <array>

#include "Keyboard.h"
#include "Mouse.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Window {
    private:
        std::array<int, 2> windowPosition = {0, 0};
        std::array<int, 2> windowSize = {0, 0};
        std::array<int, 2> viewPortSize {0, 0};
        bool updateViewport = true;
        GLFWwindow* window = NULL;
        GLFWmonitor* monitor = NULL;

        void Resize(int cx, int cy);

    public:

        void Init(int width, int height);
        static void CallbackResize(GLFWwindow* window, int cx, int cy);
        void MainLoop();
        bool IsFullScreen();
        void SetFullScreen(bool fullscreen);
};

void Window::Init(int width, int height) {
    window = glfwCreateWindow(width, height, "Main.exe", NULL, NULL);

    initKeyboard(window);
    initMouse(window);

    if(window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Error initializing window");
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, NULL);
    glfwSetWindowSizeCallback(window, Window::CallbackResize);

    monitor = glfwGetPrimaryMonitor();
    glfwGetWindowSize(window, &windowSize[0], &windowSize[1]);
    glfwGetWindowPos(window, &windowPosition[0], &windowPosition[1]);

    updateViewport = true;
}

void Window::CallbackResize(GLFWwindow* window, int cx, int cy) {
    void *windowUserPointer = glfwGetWindowUserPointer(window);

    if(Window *windowPointer = static_cast<Window*>(windowUserPointer)) {
        windowPointer -> Resize(cx, cy);
    }
}

void Window::Resize(int cx, int cy) {
    updateViewport = true;
}

void Draw() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //GLfloat vertices[] = {
    //    (SCREEN_WIDTH / 2) + 100, (SCREEN_HEIGHT / 2) + 100, 0.0,
    //    (SCREEN_WIDTH / 2) + 200, (SCREEN_HEIGHT / 2) + 100
    //};

    GLfloat vertices[] = {
        450.0, 450.0, 0.0,
        750.0, 450.0, 0.0
    };

    glLineWidth(5.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Window::MainLoop() {

    while (!glfwWindowShouldClose(window)) {
        if (updateViewport) {
            glfwGetFramebufferSize(window, &viewPortSize[0], &viewPortSize[1]);
            glViewport(0, 0, viewPortSize[0], viewPortSize[1]);
            updateViewport = false;
        }
        
        //render here
        Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

bool Window::IsFullScreen() {
    return glfwGetWindowMonitor(window) != NULL;
}

void Window::SetFullScreen(bool fullscreen) {
    if (IsFullScreen() == fullscreen) {
        return;
    }

    if (fullscreen) {
        //backup window position and window size
        glfwGetWindowPos(window, &windowPosition[0], &windowPosition[0]);
        glfwGetWindowSize(window, &windowSize[0], &windowSize[1]);

        //get resolution of monitor
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        //switch to full screen
        glfwSetWindowMonitor(window, monitor, 0, 0, mode -> width, mode -> height, 0);
    } else {
        //restore last window size and position
        glfwSetWindowMonitor(window, NULL, windowPosition[0], windowPosition[1], windowSize[0], windowSize[1], 0);
    }

    updateViewport = true;
}
