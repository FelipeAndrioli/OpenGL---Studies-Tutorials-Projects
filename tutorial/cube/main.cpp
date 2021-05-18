#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const GLfloat rotationSpeed = 10;


    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed;
                std::cout << "Arrow up" << std::endl;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed;
                std::cout << "Arrow down" << std::endl;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed;
                std::cout << "Arrow right" << std::endl;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed;
                std::cout << "Arrow left" << std::endl;
                break;
        }
    }
}

void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength) {
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] = {
        //front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom left

        //back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right

        //left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom left

        //right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom left

        //top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //bottom left

        //bottom face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  //bottom left

    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glColor3f(colour[0], colour[1], colour[2]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int main(int argc, char** argv) {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube.exe", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

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
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
        DrawCube(halfScreenHeight, halfScreenHeight, -500, 200);
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
