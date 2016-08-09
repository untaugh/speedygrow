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
  GLuint vertexShader;
  GLuint fragmentShader;
  GLuint programObject;
};

#endif // GL_HPP
