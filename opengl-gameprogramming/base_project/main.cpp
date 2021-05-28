#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "headers/Window.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char** argv) {

    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    Window window;
    window.Init(SCREEN_WIDTH, SCREEN_HEIGHT);
    //window.SetFullScreen(true);

    return 0;
}
