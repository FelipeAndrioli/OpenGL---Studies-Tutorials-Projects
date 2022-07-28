#pragma once

#include "shader.h"
#include "mesh.h"

#include <vector>
#include <string>

#include "../dependencies/assimp/include/assimp/Importer.hpp"
#include "../dependencies/assimp/include/assimp/scene.h"
#include "../dependencies/assimp/include/assimp/postprocess.h"

class Model {
    public:
        Model(char *path);
        void Draw(Shader &shader);
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType 
                type, std::string typeName);
};
