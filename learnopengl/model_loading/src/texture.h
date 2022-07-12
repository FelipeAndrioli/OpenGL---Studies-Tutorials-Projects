#pragma once

class Texture {
    public:
        Texture(const char *texture_path);
        void active();
        void bind();
        unsigned int ID;
};
