#include <iostream>
#include <windows.h>

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

#include "../dependencies/glm/glm/glm.hpp"
#include "../dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "../dependencies/glm/glm/gtc/type_ptr.hpp"

#include "temporary_vertices.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

// settings
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define KEY_PRESS_DELAY 200

bool CONFIG_MODE = false;

// Camera settings
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/*
 * TODO's
 *
 *  - Texture
 *      - Texture Map
 *  - Lighting
 *      - Material light properties
 *          - Ambient
 *          - Diffuse
 *          - Specular
 *      - Light source light properties
 *          - Ambient
 *          - Diffuse
 *          - Specular
 *  - Types of light
 *      - Directional
 *      - Point lights
 *      - Spot light
 */


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "Viewport update -> width: " << width << " height: " << height << std::endl;
}

void setConfigMode(GLFWwindow *window) {

    CONFIG_MODE = !CONFIG_MODE;
    std::string state = (CONFIG_MODE) ? "enabled" : "disabled"; 
    std::cout << "Config mode " << state << std::endl;
    
    if (CONFIG_MODE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    Sleep(KEY_PRESS_DELAY);
}

void processInput(GLFWwindow *window) {

    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        setConfigMode(window);
    }

    if (!CONFIG_MODE) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.processKeyboard(FORWARD, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.processKeyboard(BACKWARD, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.processKeyboard(LEFT, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.processKeyboard(RIGHT, deltaTime);
        }
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {

    if (CONFIG_MODE) {
        return;
    }

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

    camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
 
    if (CONFIG_MODE) {
        return;
    }   

    camera.processMouseScroll(static_cast<float>(yoffset));
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell glfw to capture our mouse
    // default = disabled
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// --------------------- 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed initializing OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // configure global opengl state 
    glEnable(GL_DEPTH_TEST);

    const char *texture_path = "C:/Users/Felipe/Documents/current_projects/OpenGL/learnopengl/model_loading/src/container2.png";
   
    Texture ModelTexture = Texture(texture_path);

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

    float ambient_strength = 0.2f;

    // application main loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        //render
        //------
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ModelTexture.active();
        ModelTexture.bind();
        ModelShader.use();
        ModelShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        ModelShader.setMat4("projection", projection);
        ModelShader.setMat4("view", view);

        // world transformations
        glm::mat4 model = glm::mat4(1.0f);
        ModelShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ImGui::Begin("Configurations");
        ImGui::SliderFloat("Ambient Strength", &ambient_strength, 0.0f, 1.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ModelShader.setFloat("ambient_strength", ambient_strength);

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
