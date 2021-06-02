#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
    According to my progress, I'm going to turn this file with only one function
    into a class with more complex and complete functions
*/

void Draw(GLint screen_width, GLint screen_height) {
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(0, screen_width, 0, screen_height, 0, 1);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    GLfloat polygonVertices[] = {
        276.0, 380.0, 0.0,
        510.0, 380.0, 0.0,
        276.0, 130.0, 0.0,
        510.0, 130.0, 0.0
    };

    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(5.0f, 5.0f, 5.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, polygonVertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}
