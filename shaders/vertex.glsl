#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoords;

void main() {
    gl_Position = projection * view * model * vec4(a_Pos, 1.0);
    texCoords = a_TexCoords;
}
