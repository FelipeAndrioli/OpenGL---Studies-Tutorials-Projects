#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <array>

#include "Window.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char** argv) {
    //GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    Window window;
    window.Init(SCREEN_WIDTH, SCREEN_HEIGHT);
    //window.SetFullScreen(true);
    window.MainLoop();

/*
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode -> redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode -> greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode -> blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode -> refreshRate);

    GLFWwindow* window = glfwCreateWindow(mode -> width, mode -> height, "Main.exe", monitor, NULL);
*/
/*
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Base Project.exe", monitor, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
*/
    //glfwSetCursorPosCallback(window, cursorPositionCallback);
/*
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetScrollCallback(window, scrollCallback);

    unsigned char pixels[16 * 16 * 4];
    memset(pixels, 0xff, sizeof(pixels));
    GLFWimage image;
    image.width = 16;
    image.height = 16;
    image.pixels = pixels;
    GLFWcursor *cursor = glfwCreateCursor(&image, 0, 0);
    glfwSetCursor(window, cursor);
*/
/*
    int screenWidth;
    int screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

    GLfloat halfSideScreen = 200;

    GLfloat vertices[] = {
        halfScreenWidth, halfScreenHeight + halfSideScreen, 0.0,
        halfScreenWidth + halfSideScreen, halfScreenHeight - halfSideScreen, 0.0,
        halfScreenWidth - halfSideScreen, halfScreenHeight - halfSideScreen, 0.0
    };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_VERTEX_ARRAY);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
*/
    return 0;
}
