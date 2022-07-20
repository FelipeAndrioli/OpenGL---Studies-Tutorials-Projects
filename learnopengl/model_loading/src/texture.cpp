#include <iostream>
#include <string>

#include "texture.h"

#include "../dependencies/glad/build/include/glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char *texture_path) {

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    int width;
    int height;
    int nrChannels;
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char *texture_data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

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
        //glBindTexture(GL_TEXTURE_2D, 0);
        glBindTexture(GL_TEXTURE_2D, ID);
 
    } else {
        std::cout << "Failed to load texture at path: " << texture_path << std::endl;
        stbi_image_free(texture_data);
    }
}

void Texture::active(int position) {
    glActiveTexture(GL_TEXTURE0 + position); 
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}






