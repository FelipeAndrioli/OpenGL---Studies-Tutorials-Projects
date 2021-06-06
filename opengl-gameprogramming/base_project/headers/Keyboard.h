#include <GLFW/glfw3.h>

class Keyboard {
    private:
    public:
        void initKeyboard(GLFWwindow *window);
};

void keyCallback (GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                std::cout << "Up arrow pressed" << std::endl;
                break;
            case GLFW_KEY_DOWN:
                std::cout << "Down arrow pressed" << std::endl;
                break;
            case GLFW_KEY_LEFT:
                std::cout << "Left arrow pressed" << std::endl;
                break;
            case GLFW_KEY_RIGHT:
                std::cout << "Right arrow pressed" << std::endl;
                break;
            case GLFW_KEY_ENTER:
                std::cout << "Enter pressed" << std::endl;
            case GLFW_KEY_ESCAPE:
                std::cout << "Escape pressed" << std::endl;
        }
    }
}

void Keyboard::initKeyboard(GLFWwindow *window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}