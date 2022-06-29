#include <iostream>

#include "shader.hpp"
#include "camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// settings
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lightsource
glm::vec3 lightPos(2.0f, 2.0f, 2.0f);

// process all input: query GLFW whether relevant keys are pressed/released this frame
// and react accordingly
// -----------------------------------------
void processInput(GLFWwindow *window) {

    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        glEnable(GL_DEPTH_TEST);
    }
    
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        glDisable(GL_DEPTH_TEST);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// glfw: whenever the mouse moves, this callback is called
// ------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// --------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// utility function for loading a 2D texture from file
// ---------------------
unsigned int loadTexture(char const *path) {
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int width;
	int height;
	int nrChannels;	

	unsigned char *texture_data = stbi_load(path, &width, &height, &nrChannels, 0);
	
	if (texture_data) {
		
		GLenum format;

		if (nrChannels == 1) {
			format = GL_RED;
		} else if (nrChannels == 3) {
			format = GL_RGB;
		} else if (nrChannels == 4) {
			format = GL_RGBA;
		} 

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D); 
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(texture_data);
		glBindTexture(GL_TEXTURE_2D, 0);
	} else {
		std::cout << "Failed to load texture at path: " << path << std::endl;
		stbi_image_free(texture_data);
	}
 
	return textureID;	
}

int main(int argv, char* argc[]) {
	// glfw: initialize and configure
	// ------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw: window creation
	// -----------------------
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, argc[0], NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed initializing the window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
	
	// tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
	// glad: load all OpenGL function pointers
	// --------------------- 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed initializing OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }
	
	// configure global opengl state
	// ---------------------------
    glEnable(GL_DEPTH_TEST);

	// build and compile the cube shader
	// -----------------------	
	const char* cube_vertex_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/multiple_lights/src/shaders/cube.vs";
    const char* cube_fragment_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/multiple_lights/src/shaders/cube.fs";
    
    Shader CubeShaderProgram = Shader(cube_vertex_shader_path, cube_fragment_shader_path);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// -------------------------	
    GLfloat vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    
	// positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};
 
	// first, configure the cube's VAO (and VBO) 
    GLuint VAO; 
    GLuint VBO; 

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); 
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	// load textures 
	// ----------------------
	unsigned int diffuseMap = loadTexture("C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/multiple_lights/src/container2.png");
	unsigned int specularMap = loadTexture("C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/multiple_lights/src/container2_specular.png");

	// shader configuration
	// ---------------------	
	CubeShaderProgram.use();
	CubeShaderProgram.setInt("material.diffuse", 0);
	CubeShaderProgram.setInt("material.specular", 1);
	
	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object, which is also a 3D cube)
	const char* light_vertex_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/multiple_lights/src/shaders/lightsource.vs";
    const char* light_fragment_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/multiple_lights/src/shaders/lightsource.fs";

	Shader LightShaderProgram(light_vertex_shader_path, light_fragment_shader_path);
   
	GLuint lightVAO;
	GLuint lightVBO;

	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);	
 
	// render loop
	// ----------------	
	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		// --------------- 
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
	
		// input
		// ---------
        processInput(window);

		// render
		// ---------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// object cube
        CubeShaderProgram.use(); 
		CubeShaderProgram.setVec3("viewPos", camera.Position);
		CubeShaderProgram.setFloat("material.shininess", 32.0f);
		
		/*
			Here we set all the uniforms the the 5/6 types of lights we have. We have to set them manually
			and index the proper PointLight struct in the array to set each uniform variable. This can be
			done more code-fiendly by defining light types as classes and set their values in there, or by
			using a more efficient uniform approach by using 'Uniform buffer objects', but that is something
			we'll discuss in the 'Advanced GLSL' tutorial.
		*/		
		// directional light
		CubeShaderProgram.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		CubeShaderProgram.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		CubeShaderProgram.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		CubeShaderProgram.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		// point light 1
		CubeShaderProgram.setVec3("pointLights[0].position", pointLightPositions[0]);
		CubeShaderProgram.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		CubeShaderProgram.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		CubeShaderProgram.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		CubeShaderProgram.setFloat("pointLights[0].constant", 1.0f);	
		CubeShaderProgram.setFloat("pointLights[0].linear", 0.09f);	
		CubeShaderProgram.setFloat("pointLights[0].quadratic", 0.032f);	
	
		// point light 2
		CubeShaderProgram.setVec3("pointLights[1].position", pointLightPositions[1]);
		CubeShaderProgram.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		CubeShaderProgram.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		CubeShaderProgram.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		CubeShaderProgram.setFloat("pointLights[1].constant", 1.0f);	
		CubeShaderProgram.setFloat("pointLights[1].linear", 0.09f);	
		CubeShaderProgram.setFloat("pointLights[1].quadratic", 0.032f);	

		// point light 3
		CubeShaderProgram.setVec3("pointLights[2].position", pointLightPositions[2]);
		CubeShaderProgram.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		CubeShaderProgram.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		CubeShaderProgram.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		CubeShaderProgram.setFloat("pointLights[2].constant", 1.0f);	
		CubeShaderProgram.setFloat("pointLights[2].linear", 0.09f);	
		CubeShaderProgram.setFloat("pointLights[2].quadratic", 0.032f);	
			
		// point light 4
		CubeShaderProgram.setVec3("pointLights[3].position", pointLightPositions[3]);
		CubeShaderProgram.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		CubeShaderProgram.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		CubeShaderProgram.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		CubeShaderProgram.setFloat("pointLights[3].constant", 1.0f);	
		CubeShaderProgram.setFloat("pointLights[3].linear", 0.09f);	
		CubeShaderProgram.setFloat("pointLights[3].quadratic", 0.032f);	
			
		// spotlight
		CubeShaderProgram.setVec3("spotLight.position", camera.Position);				
		CubeShaderProgram.setVec3("spotLight.direction", camera.Front);				
		CubeShaderProgram.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);				
		CubeShaderProgram.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);				
		CubeShaderProgram.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);				
		CubeShaderProgram.setFloat("spotLight.constant", 1.0f);				
		CubeShaderProgram.setFloat("spotLight.linear", 0.09f);				
		CubeShaderProgram.setFloat("spotLight.quadratic", 0.032f);				
		CubeShaderProgram.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));				
		CubeShaderProgram.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(20.0f)));				

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		CubeShaderProgram.setMat4("projection", projection);
		CubeShaderProgram.setMat4("view", view);

		// world transformations
		glm::mat4 model = glm::mat4(1.0f);
		CubeShaderProgram.setMat4("model", model);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// render containers
		glBindVertexArray(VAO);
		
		for (unsigned int i = 0; i < 10; i++) {
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			CubeShaderProgram.setMat4("model", model);
		
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}	

		// draw the light source object(s)
		LightShaderProgram.use();
		LightShaderProgram.setMat4("projection", projection);
		LightShaderProgram.setMat4("view", view);

		// actual rendenring
		glBindVertexArray(lightVAO);	

		for (unsigned int i = 0; i < 4; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));	// make it a smaller cube
			LightShaderProgram.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved, etc)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    CubeShaderProgram.end();

    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);
    LightShaderProgram.end();

	// glfw: terminate, clearing all previously allocated GLFW resources
	// -------------
    glfwTerminate();

    return 0;
}
