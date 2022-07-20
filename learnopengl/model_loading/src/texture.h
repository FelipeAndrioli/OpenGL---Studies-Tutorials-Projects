#pragma once

class Texture {
    public:
        Texture(const char *texture_path);
        void bind(int position);
        unsigned int ID;
};
