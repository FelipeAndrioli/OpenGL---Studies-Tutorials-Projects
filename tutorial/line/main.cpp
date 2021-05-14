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

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Line", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLfloat vertices[] = {
        100, 240, 0,
        500, 240, 0
    };

    GLfloat vertices2[] = {
        100, 300, 0,
        500, 300, 0
    };

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        //stippled line
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_LINE_STIPPLE);
        glPushAttrib(GL_LINE_BIT);
        glLineWidth(10);
        glLineStipple(1, 0x00FF);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableClientState(GL_VERTEX_ARRAY);
        glPopAttrib();
        glDisable(GL_LINE_STIPPLE);
        glDisable(GL_LINE_SMOOTH);

        //normal line
        glEnable(GL_LINE_SMOOTH);
        glPushAttrib(GL_LINE_BIT);
        glLineWidth(10);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices2);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableClientState(GL_VERTEX_ARRAY);
        glPopAttrib();
        glDisable(GL_LINE_SMOOTH);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
