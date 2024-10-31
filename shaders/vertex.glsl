#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoords;

out vec2 texCoords;

void main() {
    gl_Position = vec4(a_Pos, 1.0);
    texCoords = a_TexCoords;
}
