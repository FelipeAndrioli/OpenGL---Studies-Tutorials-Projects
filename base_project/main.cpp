#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Libraries/Output Library/Window.h"
#include "Libraries/Draw Library/Draw.h"
#include "Libraries/Input Library/Mouse.h"
#include "Libraries/Input Library/Keyboard.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char** argv) {

    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    Window window;
    window.init("Main.exe", SCREEN_WIDTH, SCREEN_HEIGHT, false);

    Draw draw;

    Mouse mouse;
    mouse.initMouse(window.getWindow());

    Keyboard keyboard;
    keyboard.initKeyboard(window.getWindow());

    while(!glfwWindowShouldClose(window.getWindow())) {
        draw.render(SCREEN_WIDTH, SCREEN_HEIGHT);
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    return 0;
}
