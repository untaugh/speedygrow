#version 130

in vec2 position;
//out vec2 Texcoord;
//uniform mat4 transform;
//uniform mat4 move;

void main() {
    //Texcoord = position.zw;
    //gl_Position = transform * move *vec4(position.xy, 0.0f, 1.0f);
    gl_Position = vec4(position, 0.0f, 1.0f);
}
