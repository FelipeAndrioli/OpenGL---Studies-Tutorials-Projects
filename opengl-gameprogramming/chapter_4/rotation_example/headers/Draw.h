#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
    According to my progress, I'm going to turn this file with only one function
    into a class with more complex and complete functions
*/

GLfloat angle = 0.0f;

void Draw(GLint screen_width, GLint screen_height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screen_width, 0, screen_height, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat polygonVertices[] = {
        276.0, 380.0, 0.0,
        510.0, 380.0, 0.0,
        276.0, 130.0, 0.0,
        510.0, 130.0, 0.0
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, polygonVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();

    std::cout << angle << std::endl;

    if (angle == 360.0) {
        angle = angle - 360.0;
    } else {
        angle += 1.0;
    }
}
