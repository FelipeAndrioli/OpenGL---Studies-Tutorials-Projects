#pragma once

class Texture {
    public:
        Texture(const char *texture_path);
        void active(int position);
        void bind();
        unsigned int ID;
};
