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

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World.exe", NULL, NULL);

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

    GLfloat halfSideLength = 200;

    GLfloat vertices_triangle[] = {
        halfScreenWidth, halfScreenHeight + halfSideLength, -1.0,                   //top corner
        halfScreenWidth + halfSideLength, halfScreenHeight - halfSideLength, -1.0,  //right corner
        halfScreenWidth - halfSideLength, halfScreenHeight - halfSideLength, 0.0,   //left corner
    };

    GLfloat color_triangle[] = {
        255, 0, 0,
        255, 0, 0,
        255, 0, 0
    };

    GLfloat vertices_polygon[] = {
        halfScreenWidth - halfSideLength, halfScreenHeight + halfSideLength, 0.0,   //top left corner
        halfScreenWidth, halfScreenHeight, 0.0,                                     //middle corner
        halfScreenWidth, halfScreenHeight - halfSideLength, 0.0,                    //middle bottom corner
        halfScreenWidth - halfSideLength, halfScreenHeight - halfSideLength, 0.0,   //left bottom corner
        halfScreenWidth - halfScreenWidth, halfScreenHeight, 0.0                    //left middle corner
    };

    GLfloat color_polygon[] = {
        0, 0, 255,
        0, 0, 255,
        0, 0, 255,
        0, 0, 255,
        0, 0, 255
    };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices_triangle);
        glColorPointer(3, GL_FLOAT, 0, color_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices_polygon);
        glColorPointer(3, GL_FLOAT, 0, color_polygon);
        glDrawArrays(GL_POLYGON, 0, 5);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
