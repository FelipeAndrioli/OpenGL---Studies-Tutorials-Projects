#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "Failed initializing the library, ending application." << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Point.exe", NULL, NULL);

    int screenWidth;
    int screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*
    Specifies the part of the window to which OpenGL will draw (in pixels), convert from 
    normalised to pixels
    */
    glViewport(0.0f, 0.0f, screenWidth, screenHeight); 

    /*
    Projection matrix defines the properties of the camera that views the objects in the 
    world coordinate frame. Here you typically set the zoom factor, aspect ratio and the 
    near and far clipping planes
    */
    glMatrixMode(GL_PROJECTION);

    /*
    Replace the current matrux with the identity matrix and starts us a fresh because 
    matrix transforms such as glOrpho and glRotate cumulate, basically put us at (0, 0, 0)
    */
    glLoadIdentity(); 

    /*
    Essentially set coordinate system
    */
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);

    /*
    (default matrix mode) modelview matrix defines how your object are transformed 
    (meaning translation, rotation and scaling) in your world
    */
    glMatrixMode(GL_MODELVIEW);

    /*
    Same as above comentary at the same function
    */
    glLoadIdentity();

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
    GLfloat halfSideLength = 200;

    GLfloat pointVertex[] = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    GLfloat pointVertex2[] = {SCREEN_WIDTH * 0.75, SCREEN_HEIGHT / 2};
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        /*
        make the point circular
        */
        glEnable(GL_POINT_SMOOTH);

        /*
        tell OpenGL that you're using a vertex array for fixed-function attribute
        */
        glEnableClientState(GL_VERTEX_ARRAY);

        /*
        Must be added before glDrawArrays is called
        */
        glPointSize(50);

        /*
        Point to the vertices to be used
        */
        glVertexPointer(2, GL_FLOAT, 0, pointVertex); 

        /*
        draw the vertices
        */
        glDrawArrays(GL_POINTS, 0, 1);

        /*
        tell OpenGL that you're finished using the vertex array attribute
        */
        glDisableClientState(GL_VERTEX_ARRAY);

        /*
        stop the smoothing to make points circular
        */
        glDisable(GL_POINT_SMOOTH);

        /*
        tell OpenGL that you're using a vertex array for fixed-function attribute
        */
        glEnableClientState(GL_VERTEX_ARRAY);

        /*
        Point to the vertices to be used
        */
        glVertexPointer(2, GL_FLOAT, 0, pointVertex2);

        glPointSize(10);

        /*
        draw the vertices
        */
        glDrawArrays(GL_POINTS, 0, 1);

        /*
        Tell OpenGL that you're finished using the vertex array attribute
        */
        glDisableClientState(GL_VERTEX_ARRAY);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
