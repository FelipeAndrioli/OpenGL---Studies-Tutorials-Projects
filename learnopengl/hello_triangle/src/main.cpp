#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void defaultHelloTriangle() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // build and compile our shader program
    // ================ VERTEX SHADER ======================== 

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // checking for shader compiling errors
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ==================== FRAGMENT SHADER =======================
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // checking for shader compiling errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ======================== LINK SHADERS =========================
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // deleting linked shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3     // second triangle
    };

    /*
        Vertex Buffer Object(VBO_t1) -> When the vertex data is defined, we'd like to send it as
        input to the first process of the graphics pipeline: the vertex shader. This is done by
        creating memory on the GPU where we store the vertex data, configure how OpenGL should
        interpret the memory and specify how to send the data to the graphics card. The vertex
        shader then processes as much vertices as we tell it to from its memory.

        We manage this memory via so called vertex buffer objects (VBO_t1) that can store a large
        number of vertices in the GPU's memory. The advantage of using those buffer objects is
        that we can send large batches of data all at once to the graphics card, and keep it there
        if there's enough memory left, without having to send data one vertex at a time. Sending
        data to the graphics card from the CPU is relatively slow, so wherever we can we try to
        send as much data as possible at once. Once the data is in the graphics card's memory the
        vertex shader has almost instant access to the vertices making it extremely fast.

        Vertex Array Object(VAO_t1) -> A vertex array object can be bound just like a vertex buffer
        object and any subsequent vertex attribute calls from that point on will be stored inside
        the VAO_t1. This has the advantage that when configuring vertex attribute pointers you only
        have to make those calls once and whenever we want to draw the object, we can just bind
        the corresponding VAO_t1. This makes switching between different vertex data and attribute
        configuration as easy as binding a different VAO_t1. All the state we just set is stored 
        inside the VAO_t1.

        A Vertex Array Object is an OpenGL Object that stores all of the state needed to supply
        vertex data. It stores the format of the vertex data as well as the Buffer Objects providing
        the vertex data arrays. Note that VAO_t1s do not copy, freeze or store the contents of the
        referenced buffers - if you change any of the data in the buffers referenced by an existing
        VAO_t1, those changes will be seen by users of the VAO_t1.

        Element Buffer Object(EBO) -> An EBO is a buffer, just like a vertex buffer object, that
        stores indices that OpenGL uses to decide what vertices to draw. This is so called indexed
        drawing. Similar to the VBO_t1 we bind the EBO and copy the indices into the buffer with 
        glBufferData. Also, just like the VBO_t1 we want to place those calls between a bind and an
        unbind call, although this time we specify GL_ELEMENT_ARRAY_BUFFER as the buffer type.
    */

    unsigned int EBO;
    unsigned int VBO_t1;
    unsigned int VAO_t1;

    glGenVertexArrays(1, &VAO_t1);
    glGenBuffers(1, &VBO_t1);
    glGenBuffers(1, &EBO);

    // binding the vertex array object first, then bind and set vertex buffer(s), and then
    // configure vertex attribute(s).
    glBindVertexArray(VAO_t1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_t1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO_t1 as the vertex
    // attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO_t1 afterwards so other VAO_t1 calls won't accidentally modify this VAO_t1,
    // but this rarely happens. Modifying other VAO_t1s requires a call to glBindVertexArray anyways
    // so we generally don't unbind VAO_t1s (nor VBO_t1s) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // drawing the driangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO_t1); // seeing as we only have a single VAO_t1 there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
        // glBindVertexArray(0); // no need to unbind it every time

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional -> de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO_t1);
    glDeleteBuffers(1, &VBO_t1);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}

void firstExercise() {
    /*
        - Initialize glfw
            - Versions
            - Profile
        - Create window
        - Make the window context the current
        - Check glad
        - Set viewport
        - Set render loop
            - Clear color
            - Swap buffers
            - Poll events
        - Create shaders
            - Vertex Shader
            - Fragment Shader
        - Create shader program
            - Link shaders
        - Create vertices
        - Create Vertex Buffer
            - Copy vertices
                - Bind
                - Copy data
            - Set the vertex attributes pointers
            - Set the shader program
        - Draw the object
    */

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle Exercises", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed initializing the window" << std::endl;
        glfwTerminate(); 
        return;
    }

    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int success;
    char infoLog[512];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //vertices using EBO
    GLfloat vertices[] = {
        -0.5f, 0.1f, 0.0f,  // down t1
        -1.0f, 0.5f, 0.0f,  // left t1
        0.0f, 0.5f, 0.0f,   // right t1 and left t2
        0.5f, 0.1f, 0.0f,   // down t2
        1.0f, 0.5f, 0.0f    // right t2
    };

    GLuint indices[] = {
        0, 1, 2,    //first triangle    
        2, 3, 4,    //second triangle 
        0, 2, 3     //third triangle 
    };

/*
    //vertices using only VAO_t1 and VBO_t1
    GLfloat vertices[] = {
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f,

        0.0f, -0.5f, 0.0f,
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f
    };
*/
    GLuint VBO_t1;
    GLuint VAO_t1;
    GLuint EBO;

    glGenVertexArrays(1, &VAO_t1);
    glGenBuffers(1, &VBO_t1);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO_t1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_t1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO_t1);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO_t1);
    glDeleteBuffers(1, &VBO_t1);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void secondExercise() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Second exercise", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed initializing window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shaderProgram = glCreateProgram();

    int success;
    char infoLog[512];

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);    

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices_t1[] = {
        -1.0f, 1.0f, 0.0f,  //left
        -0.5f, 0.1f, 0.0f,  //down
        0.0f, 1.0f, 0.0f    //right
    };

    GLfloat vertices_t2[] = {
        1.0f, -1.0f, 0.0f,  //right
        0.5f, -0.1f, 0.0f,  //top
        0.0f, -1.0f, 0.0f   //left
    };

    GLuint VAOs[2];
    GLuint VBOs[2];

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_t1), vertices_t1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); 

    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_t2), vertices_t2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
       
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs); 
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

int main(int argc, char** argv) {

    //defaultHelloTriangle();
    firstExercise();
    //secondExercise();

    return 0;
}
