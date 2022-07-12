#version 330 core

/*
    Fragment Shader -> Calculate the color of the fragment
*/

uniform float color_r;
uniform float color_g;
uniform float color_b;
uniform float color_a;

uniform vec3 colors;

out vec4 FragColor;

void main() {
   //FragColor = vec4(color_r, color_g, color_b, color_a); 
   FragColor = vec4(colors, 1.0);
}
