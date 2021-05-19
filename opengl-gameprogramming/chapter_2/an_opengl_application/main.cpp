#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
GLfloat halfSideLength = 200;

class Triangle {
    private:
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> color;

    public:
        void defineVertices(std::vector<GLfloat>);
        void defineColor(std::vector<GLfloat>);
        void drawTriangle();
};

void Triangle::defineVertices(std::vector<GLfloat> new_vertices) {
    vertices = new_vertices;
}

void Triangle::defineColor(std::vector<GLfloat> new_color) {
    color = new_color;
}

void Triangle::drawTriangle() {

    static float alpha = 0.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(alpha, 0.0, 0.0, 1.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glColorPointer(3, GL_FLOAT, 0, color.data());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    alpha += 1;
}

int main(int argc, char** argv) {

    Triangle myTriangle;

        std::vector<GLfloat> vertices = {
            -0.6f, -0.4f, 0.0f,
            0.6f, -0.4f, 0.0f,
            0.0f, 0.6f, 0.0f
        };

        std::vector<GLfloat> colors = {
            0.0, 255, 0.0,
            0.0, 255, 0.0,
            0.0, 255, 0.0
        };


    myTriangle.defineVertices(vertices);
    myTriangle.defineColor(colors);

    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "The application have failed initializing the library" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "An OpenGL Application.exe", NULL, NULL);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myTriangle.drawTriangle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
