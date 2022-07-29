#pragma once

#include "shader.h"
#include "mesh.h"

#include <vector>
#include <string>

#include "../dependencies/assimp/include/assimp/Importer.hpp"
#include "../dependencies/assimp/include/assimp/scene.h"
#include "../dependencies/assimp/include/assimp/postprocess.h"

#include "stb_image.h"

#include "../dependencies/glad/build/include/glad/glad.h"
#include "../dependencies/glfw/include/GLFW/glfw3.h"

class Model {
    public:
        // model data 
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;

        // constructor, expects a filepath to a 3D model 
        Model(char *path);
        // draws the model, and thus all its meshes 
        void Draw(Shader &shader);
    private:
        // loads a model with supporeted ASSIMP extensions from file and stores
        // the resulting meshes in the meshes vector.
        void loadModel(std::string path);

        // processes a node in a recursive fashion. Processes each individual
        // mesh located at the node and repeats this process on its children
        // nodes (if any).
        void processNode(aiNode *node, const aiScene *scene);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
       
        // checks all material textures of a given type and loads the textures
        // if they're not loaded yet. the required info is returned as a 
        // Texture struct
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType
                type, std::string typeName);

        unsigned int TextureFromFile(const char *path, const std::string 
                &directory, bool gamma = false);
};
