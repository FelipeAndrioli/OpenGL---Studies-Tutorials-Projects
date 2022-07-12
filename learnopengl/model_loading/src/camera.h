#pragma once 

//#include <glm/glm.hpp>
#include "../dependencies/glm/glm/glm.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
    public:
        // attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // Euler angles
        float Yaw;
        float Pitch;

        // Camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // Constructor with vectors
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);  

        // Constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float picth = PITCH);

        // Returns the view matrix calculated using Euler Angles and the 
        // LookAt Matrix
        glm::mat4 getViewMatrix();

        // Processes input received from any keyboard-like input system. 
        // Accept input parameter in the form of camera defined ENUM (to
        // abstract it from windowing systems)
        void processKeyboard(Camera_Movement direction, float deltaTime);

        // process input received from a mouse input system. Expects the
        // offset value in both x and y direction
        void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

        // Process input received from a mouse scroll-wheel event. Only
        // requires input on the vertical wheel-axis
        void processMouseScroll(float yoffset);

    private:
        void updateCameraVectors();
        glm::mat4 lookAt(glm::vec3 positionVector, glm::vec3 targetVector, glm::vec3 upWorldVector);
};










