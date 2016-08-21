#ifndef GL_H
#define GL_H

#include <GL/glew.h>
#include "world.hpp"

class Gl
{
public:
  Gl();
  void init(void);
  void resize(int width, int height);
  void render(void);
  GLuint compileShader(GLenum type, const GLchar *source);
  GLuint fileToShader(GLenum type, const GLchar *filename);
  void linkProgram(GLuint program);
  GLuint vao2;
  GLuint circleVertexShader;
  GLuint circleFragmentShader;
  GLuint circleProgram;
  World *world;
  GLuint vbo;
  GLfloat circleVertices[1000];
};

#endif // GL_HPP
