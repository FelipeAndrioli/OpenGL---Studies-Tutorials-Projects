#include <iostream>

//#include <glad/glad.h>
#include "../dependencies/glad/build/include/glad/glad.h"
//#include <GLFW/glfw3.h> 
#include "../dependencies/glfw/include/GLFW/glfw3.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_glfw.h"
#include "../dependencies/imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "temporary_vertices.h"
#include "shader.h"

// settings
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/*
 * TODO's
 *
 *  - Texture
 *      - Class?
 *      - Texture Map
 *  - Camera
 *      - Class
 *      - callbacks
 *  - Lighting
 *      - Material light properties
 *      - Light source light properties
 *  - Types of light
 *
 * */

unsigned int loadTexture(const char *path) {
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

        // Texture wrapping/filtering options
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

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "Viewport update -> width: " << width << " height: " << height << std::endl;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {

}

int main(int argc, char* argv[]) {

    // glfw: ininial configuration
    // ---------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: initializing window
    // -------------------------
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, argv[0], nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed generating window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell glfw to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// --------------------- 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed initializing OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // configure global opengl state 
    //glEnable(GL_DEPTH_TEST);

    const char *texture_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/model_loading/src/container2.png";
   
    unsigned int model_texture = loadTexture(texture_path); 

    unsigned int VAO;
    unsigned int VBO;

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

    // shaders
    const char *vertex_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/model_loading/src/shaders/shader.vs";
    const char *fragment_shader_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/model_loading/src/shaders/shader.fs";

    Shader ModelShader = Shader(vertex_shader_path, fragment_shader_path, nullptr);
    ModelShader.use();
    ModelShader.setInt("m_texture", 0);
    
    // imgui initialization
    // --------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); 
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float model_r = 0.0f;
    float model_g = 0.0f;
    float model_b = 0.0f;

    glm::vec4 colors_vec;
    colors_vec.x = model_r;
    colors_vec.y = model_g;
    colors_vec.z = model_b;

    // application main loop
    while (!glfwWindowShouldClose(window)) {
        //render
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        processInput(window);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model_texture);
        ModelShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ImGui::Begin("Configurations");
        ImGui::SliderFloat("Model R", &model_r, 0.0f, 1.0f); 
        ImGui::SliderFloat("Model G", &model_g, 0.0f, 1.0f); 
        ImGui::SliderFloat("Model B", &model_b, 0.0f, 1.0f); 
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        colors_vec.x = model_r;
        colors_vec.y = model_g;
        colors_vec.z = model_b;
        ModelShader.setVec3("colors", colors_vec);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved, etc)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    ModelShader.end();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate(); 

    return 0;
}
