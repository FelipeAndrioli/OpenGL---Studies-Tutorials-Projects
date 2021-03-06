#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
    According to my progress, I'm going to turn this file with only one function
    into a class with more complex and complete functions
*/

class Draw {
	private:
	public:
		void render(GLint screen_width, GLint screen_height);
		void positionAndRotate(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
};

void Draw::render(GLint screen_width, GLint screen_height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-screen_width / 2, screen_width / 2, -screen_height / 2, screen_height / 2, -50.0, 50.0);
    //glFrustum(-screen_width / 2, screen_width / 2, -screen_height / 2, screen_height / 2, -50.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat cube_vertices[] =  {
		//face
		30.0, 30.0, 30.0,	//top right
		30.0, -30.0, 30.0,	//bottom right
		-30.0, -30.0, 30.0,	//bottom left
		-30.0, 30.0, 30.0,	//top left

		//top
		30.0, 30.0, 30.0,	//front right
		30.0, 30.0, -30.0,	//back right
		-30.0, 30.0, -30.0,	//back left
		-30.0, 30.0, 30.0,	//front left

		//bottom
		30.0, -30.0, 30.0,	//front right
		30.0, -30.0, -30.0,	//back right
		-30.0, -30.0, -30.0,	//back left
		-30.0, -30.0, 30.0,	//front left

		//left
		-30.0, 30.0, 30.0,	//front top
		-30.0, -30.0, 30.0,	//front bottom
		-30.0, -30.0, -30.0,	//back bottom
		-30.0, 30.0, -30.0,	//back top

		//right
		30.0, 30.0, 30.0,	//front top
		30.0, -30.0, 30.0,	//front bottom
		30.0, -30.0, -30.0,	//back bottom
		30.0, 30.0, -30.0,	//back top

		//back
		30.0, 30.0, -30.0,	//back top right
		30.0, -30.0, -30.0,	//back bottom right
		-30.0, -30.0, -30.0, 	//back bottom left
		-30.0, 30.0, -30.0	//back top left
    };

    GLfloat cube_colors[] = {
		1.0, 1.0, 0.0,
		1.0, 1.0, 0.0,
		1.0, 1.0, 0.0,
		1.0, 1.0, 0.0,

		1.0, 0.0, 1.0,
		1.0, 0.0, 1.0,
		1.0, 0.0, 1.0,
		1.0, 0.0, 1.0,

		1.0, 0.0, 0.0, 
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,

		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,

		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,

		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
	positionAndRotate(129, 113, 15, 35, 21, 12);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
    glColorPointer(3, GL_FLOAT, 0, cube_colors);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glPopMatrix();
}

void Draw::positionAndRotate(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) {
	glTranslatef(xPos, yPos, zPos);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
}