#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void keyCallback (GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                std::cout << "Up arrow pressed" << std::endl;
                break;
            case GLFW_KEY_DOWN:
                std::cout << "Down arrow pressed" << std::endl;
                break;
            case GLFW_KEY_LEFT:
                std::cout << "Left arrow pressed" << std::endl;
                break;
            case GLFW_KEY_RIGHT:
                std::cout << "Right arrow pressed" << std::endl;
                break;
        }
    }
}

static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    std::cout << xpos << " : " << ypos << std::endl;
}

void cursorEnterCallback(GLFWwindow *window, int entered) {
    if (entered) {
        std::cout << "Entered Window" << std::endl;
    }
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    double ypos;
    double xpos;

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        std::cout << "Right button pressed" << std::endl;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << xpos << " : " << ypos << std::endl;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Left button pressed" << std::endl;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << xpos << " : " << ypos << std::endl;
    }
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    std::cout << xoffset << " : " << yoffset << std::endl;
}

int main(int argc, char** argv) {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Base Project.exe", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    //glfwSetCursorPosCallback(window, cursorPositionCallback);
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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
