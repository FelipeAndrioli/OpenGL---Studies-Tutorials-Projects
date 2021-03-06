#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <array>
#include <math.h>

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

void DrawCircle(float radius, int numberOfSides, bool edgeOnly) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLdouble middle_width = SCREEN_WIDTH / 2;
    GLdouble middle_height = SCREEN_HEIGHT / 2;
    GLint circle_edges = numberOfSides + 1;

    GLdouble circleVerticesX[circle_edges];
    GLdouble circleVerticesY[circle_edges];
    GLdouble circleVerticesZ[circle_edges];

    GLdouble circle_vertices[circle_edges * 3];

    for (int i = 0; i < circle_edges; i++) {
        circleVerticesX[i] = middle_width + radius * cos(M_PI * i / 180.0);
        circleVerticesY[i] = middle_height + radius * sin(M_PI * i / 180.0);
        circleVerticesZ[i] = 0.0;
    }

    for (int i = 0; i < circle_edges; i++) {
        circle_vertices[i * 3] = circleVerticesX[i];
        circle_vertices[i * 3 + 1] = circleVerticesY[i];
        circle_vertices[i * 3 + 2] = circleVerticesZ[i];
    }

    if (edgeOnly) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, circle_vertices);
        glDrawArrays(GL_LINE_STRIP, 0, circle_edges);
        glDisableClientState(GL_VERTEX_ARRAY);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, circle_vertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle_edges);
        glDisableClientState(GL_VERTEX_ARRAY);    
    }
}

void Window::MainLoop() {
    while (!glfwWindowShouldClose(window)) {
        if (updateViewport) {
            glfwGetFramebufferSize(window, &viewPortSize[0], &viewPortSize[1]);
            glViewport(0, 0, viewPortSize[0], viewPortSize[1]);
            updateViewport = false;
        }
        
        //render here
        DrawCircle(200.0, 361, true);

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