#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <array>

/*
    According to my progress, I'm going to turn this file with only one function
    into a class with more complex and complete functions
*/

void Draw(GLint screen_width, GLint screen_height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screen_width, 0, screen_height, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat polygonVertices[] = {
        320, 240, 0,
        370, 290, 0,
        420, 240, 0,
        370, 190, 0
    };

    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, polygonVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}
