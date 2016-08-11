#ifndef GL_H
#define GL_H

#include <GL/glew.h>

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
  GLuint vertexShader;
  GLuint fragmentShader;
  GLuint programObject;
  GLuint mTextureID;
  GLuint vao2, vao1;
  GLuint circleVertexShader;
  GLuint circleFragmentShader;
  GLuint circleProgram;
};

#endif // GL_HPP
