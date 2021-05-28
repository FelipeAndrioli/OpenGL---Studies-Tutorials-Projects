#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <array>

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

    int screenWidth;
    int screenHeight;

    glfwGetWindowSize(window, &screenWidth, &screenHeight);

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        std::cout << "Right button pressed" << std::endl;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << xpos << " : " << ypos << std::endl;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Left button pressed" << std::endl;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << xpos << " : " << screenHeight - ypos << std::endl;
    }
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    std::cout << xoffset << " : " << yoffset << std::endl;
}

GLFWcursor* createDefaultCursor() {
    return glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
}

GLFWcursor* createPersonCursor(bool standard_cursor) {

    /*
        Create a personalized cursor, might be useful sometime
    */

    unsigned char pixels[16 * 16 * 4];
    memset(pixels, GLFW_ARROW_CURSOR, sizeof(pixels));

    GLFWimage image;
    image.width = 16;
    image.height = 16;
    image.pixels = pixels;
    GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);

    return cursor;
}

void initMouse(GLFWwindow* window) {
    //glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetScrollCallback(window, scrollCallback);

    GLFWcursor* cursor = createDefaultCursor();
    glfwSetCursor(window, cursor);
}
