#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char** argv) {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Joystick Input.exe", NULL, NULL);

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
        glClear(GL_COLOR_BUFFER_BIT);

        int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

        if (present) {
            int axesCount;
            const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

            std::cout << "Left Stick X Axis: " << axes[0] << std::endl; // tested with PS4 controller connected via micro USB cable
            std::cout << "Left Stick Y Axis: " << axes[1] << std::endl; // tested with PS4 controller connected via micro USB cable
            std::cout << "Right Stick X Axis: " << axes[2] << std::endl; // tested with PS4 controller connected via micro USB cable
            std::cout << "Right Stick Y Axis: " << axes[3] << std::endl; // tested with PS4 controller connected via micro USB cable
            std::cout << "Left Trigger/L2: " << axes[4] << std::endl; // tested with PS4 controller connected via micro USB cable
            std::cout << "Right Trigger/R2: " << axes[5] << std::endl; // tested with PS4 controller connected via micro USB cable
        
           int buttonCount;
           const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

           if (GLFW_PRESS == buttons[1]) {
               std::cout << "Pressed" << std::endl;
           } else if (GLFW_RELEASE == buttons[0]) {
               std::cout << "Released" << std::endl;
           }

           const char *name = glfwGetJoystickName(GLFW_JOYSTICK_1);
           std::cout << name << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
