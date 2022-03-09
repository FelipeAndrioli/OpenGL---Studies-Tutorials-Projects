#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D my_texture_one;
uniform sampler2D my_texture_two;

// exercise 4
uniform float alternancy;

void main() {
    // exercise 1
    //FragColor = mix(texture(my_texture_one, TexCoord), texture(my_texture_two, vec2(TexCoord.x, -TexCoord.y)), 0.2);
    // exercise 1 variation
    //FragColor = mix(texture(my_texture_one, TexCoord), texture(my_texture_two, vec2(-TexCoord.x, TexCoord.y)), 0.2);
    
    // default
    //FragColor = mix(texture(my_texture_one, TexCoord), texture(my_texture_two, TexCoord), 0.2);

    // exercise 4
    FragColor = mix(texture(my_texture_one, TexCoord), texture(my_texture_two, TexCoord), alternancy);
}

