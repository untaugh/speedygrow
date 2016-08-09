#version 130

in vec2 Texcoord;
uniform sampler2D image;
out vec4 color;

void main() {
  color = texture(image, Texcoord);
}
