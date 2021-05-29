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

    //starting point 40, 40
    glPointSize(4.0);

    for (GLdouble y = 10; y < 50; y += 10) {
        for (GLdouble x = 10; x < 50; x += 10) {
            
            /*
            // Point grid
            GLdouble point_position_x = x * 5;
            GLdouble point_position_y = y * 5;

            GLdouble point_vertices[] = {
                point_position_x, point_position_y, 0.0
            };

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, point_vertices);
            glDrawArrays(GL_POINTS, 0, 1);
            glDisableClientState(GL_VERTEX_ARRAY);

            */

            /*
            // Triangle grid

            GLdouble starting_triangle_position_x = (x * 5);

            GLdouble triangle_vertices[] = {
                starting_triangle_position_x, y * 5, 0.0,
                starting_triangle_position_x + 50.0, y * 5, 0.0,
                starting_triangle_position_x, y * 5 + 50.0, 0.0
            };

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, triangle_vertices);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableClientState(GL_VERTEX_ARRAY);

            */

            

            // Filled square grid

            GLdouble starting_quad_position_x = x * 5;
            GLdouble starting_quad_position_y = y * 5;

            GLdouble quad_colors[] = {
                1.0, 1.0, 1.0,
                1.0, 1.0, 1.0,
                1.0, 1.0, 1.0,
                1.0, 1.0, 1.0
            };

            GLdouble quad_vertices[] = {
                starting_quad_position_x, starting_quad_position_y, 0.0,
                starting_quad_position_x + 50.0, starting_quad_position_y, 0.0,
                starting_quad_position_x + 50.0, starting_quad_position_y + 50.0, 0.0,
                starting_quad_position_x, starting_quad_position_y + 50.0, 0.0
            };

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);        
            glVertexPointer(3, GL_DOUBLE, 0, quad_vertices);
            glColorPointer(3, GL_DOUBLE, 0, quad_colors);
            glDrawArrays(GL_QUADS, 0, 4);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);

            

           /*

           GLdouble starting_position_x = x * 5;
           GLdouble starting_position_y = y * 5;

            GLdouble triangle_strip_vertices[] = {
                starting_position_x, starting_position_y, 0.0,
                starting_position_x + 50.0, starting_position_y, 0.0, 
                starting_position_x, starting_position_y + 50.0, 0.0,
                starting_position_x + 50.0, starting_position_y + 50.0, 0.0
            };

            GLdouble triangle_strip_colors[] = {
                1.0, 1.0, 1.0,
                1.0, 1.0, 1.0,
                1.0, 1.0, 1.0,
                1.0, 1.0, 1.0
            };

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, triangle_strip_vertices);
            glColorPointer(3, GL_DOUBLE, 0, triangle_strip_colors);
            glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            */

        }
    }  
}

void Window::MainLoop() {
    while (!glfwWindowShouldClose(window)) {
        if (updateViewport) {
            glfwGetFramebufferSize(window, &viewPortSize[0], &viewPortSize[1]);
            glViewport(0, 0, viewPortSize[0], viewPortSize[1]);
            updateViewport = false;
        }
        
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