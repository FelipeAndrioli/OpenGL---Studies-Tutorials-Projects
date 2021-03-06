#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// exercise 4
float alternancy = 0.2;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// exercise 4
void changeAlternancy(int key) {
    GLint current_shader_program = 0;

    glGetIntegerv(GL_CURRENT_PROGRAM, &current_shader_program);

    if (key == GLFW_KEY_UP && alternancy < 1.0) {
        alternancy += 0.01;
    } else if (key == GLFW_KEY_DOWN && alternancy > 0.0) {
        alternancy -= 0.01;
    }

    glUniform1f(glGetUniformLocation(current_shader_program, "alternancy"), alternancy);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        changeAlternancy(GLFW_KEY_UP);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        changeAlternancy(GLFW_KEY_DOWN);
    }
}

int main(int argc, char** argv) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed initializing window..." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    const char* vertex_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/textures/src/shaders/shader.vs";
    const char* fragment_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/textures/src/shaders/shader.fs";

    Shader ShaderProgram = Shader(vertex_shader_path, fragment_shader_path);

    unsigned int texture1;
    unsigned int texture2;

    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    // default wrapping options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // exercise 2
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // exercise 3 - wrapping options
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // exercise 3 - filtering options
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width;
    int height;
    int nrChannels;
    unsigned char *data = stbi_load("C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/textures/src/container.jpg", &width, &height, &nrChannels, 0);

    stbi_set_flip_vertically_on_load(true);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        /*
            This is a large function with quite a few parameters so we'll walk through them step-by-step:
                - The first argument specifies the texture target; setting this to GL_TEXTURE_2D means this
                operation will generate a texture on the currently bound texture object at the same target
                (so any textures bound to targets GL_TEXTURE_1D or GL_TEXTURE_3D will not be affected).
                - The second argument specifies the mipmap level for which we want to create a texture for
                if you want to set each mipmap level manually, but we'll leave it at the base level which
                is 0.
                - The third argument tells OpenGL in what kind of format we want to store the texture. Our
                image has only RGB values so we'll store the texture with RGB values as well.
                - The 4th and 5th argument sets the width and height of the resulting texture. We stored those
                earlier when loading the image so we'll use the corresponding values.
                - The next argument should always be 0 (some legacy stuff).
                - The 7th and 8th argument specify the format and datatype of the source image. We loaded the
                image with RGB values and stored them as chars (bytes) so we'll pass in the corresponding values.
                - The last argument is the actual image data.            
        */

        glGenerateMipmap(GL_TEXTURE_2D);
        /*
            Once the glTexImage2D is called, the currently bound texture object now has the texture image attached
            to it. However, currently it only has the base-level of the texture image loaded and if we wannt to use
            mipmaps we have to specify all the different images manually (by continually incrementing the second
            argument) or, we could call glGenerateMipmap after generating the texture. This will automatically
            generate all the required mipmaps for the currently bound texture.
        */
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);

    // texture 2

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // default wrapping options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // exercise 2
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // filtering options 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // exercise 3 - filtering options
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // load texture image
    data = stbi_load("C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/textures/src/awesomeface.png", &width, &height, &nrChannels, 0);

    if (data) {
        // set up everything together
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        // create mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data); 

    ShaderProgram.use();
    glUniform1i(glGetUniformLocation(ShaderProgram.ID, "my_texture_one"), 0);
    ShaderProgram.setInt("my_texture_two", 1);
    ShaderProgram.setFloat("alternancy", alternancy);

    GLfloat vertices[] = {
        // positions        // colors       // texture coords       
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,         // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,        // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,       // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f         // top left
    };

    // exercise 2
    /* 
    GLfloat vertices[] = {
        // positions        // colors       // texture coords       
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f,         // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,        // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,       // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f         // top left
    };
    */

    // exercise 3
    /*
    GLfloat vertices[] = {
        // positions     // colors       // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.55f, 0.55f,         // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.55f, 0.45f,        // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.45f, 0.45f,       // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.45f, 0.55f         // top left
    };
    */

    GLuint indices[] = {
        0, 1, 3,    // first triangle
        3, 2, 1     // second triangle
    };

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // render container
        ShaderProgram.use(); 
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    //glDeleteProgram(shader_program);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    return 0;
}
