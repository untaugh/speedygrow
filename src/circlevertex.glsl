#version 130

in vec2 position;
uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 0.0f, 1.0f);
}
