#include "gl.hpp"
#include <SDL.h>
#include <iostream>
#include "alien.h"
#include "circle.hpp"

Gl::Gl()
{
}

void Gl::init(void)
{
  GLenum err = glewInit();
  if (err != GLEW_OK)
    {
      exit(1);
    }

  if (!GLEW_VERSION_2_1)
    {
      exit(1);
    }
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glGenTextures(1, &mTextureID );
  glBindTexture(GL_TEXTURE_2D, mTextureID );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, alien.width, alien.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, alien.pixel_data );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glClearColor(1.0, 0.9, 1.0, 1.0);

  vertexShader = fileToShader(GL_VERTEX_SHADER, "src/vertex.glsl");
  fragmentShader = fileToShader(GL_FRAGMENT_SHADER, "src/fragment.glsl");

  circleVertexShader = fileToShader(GL_VERTEX_SHADER, "src/circlevertex.glsl");
  circleFragmentShader = fileToShader(GL_FRAGMENT_SHADER, "src/circlefragment.glsl");  
  
  programObject = glCreateProgram();
  glAttachShader(programObject, vertexShader);
  glAttachShader(programObject, fragmentShader);
  linkProgram(programObject);

  circleProgram = glCreateProgram();
  glAttachShader(circleProgram, circleVertexShader);
  glAttachShader(circleProgram, circleFragmentShader);
  linkProgram(circleProgram);

  glUseProgram(circleProgram);

  world = new World();
  world->generate(10);

  vao2 = 2;
  glGenVertexArrays(1, &vao2);
  glBindVertexArray(vao2);

  // create buffers
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), NULL, GL_STREAM_DRAW);
  
  GLuint circlePosAttrib = glGetAttribLocation(programObject, "position");
  glVertexAttribPointer(circlePosAttrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(circlePosAttrib);

  glUseProgram(programObject);

  GLfloat vertices[] = {
  //  Position              Texcoords
      32.0f,  32.0f, 1.0f, 0.0f, // Top-right
      0.0f,  32.0f, 0.0f, 0.0f, // Top-left
       32.0f, 0.0f, 1.0f, 1.0f, // Bottom-right
       0.0f,  0.0f, 0.0f, 1.0f,  // Bottom-left

      132.0f,  132.0f, 1.0f, 0.0f, // Top-right
      100.0f,  132.0f, 0.0f, 0.0f, // Top-left
      132.0f, 100.0f, 1.0f, 1.0f, // Bottom-right
     100.0f,  100.0f, 0.0f, 1.0f,  // Bottom-left
  };

  vao1 = 1;
  glGenVertexArrays(1, &vao1);
  glBindVertexArray(vao1);

  // create buffers
  glGenBuffers(1, &vbo2);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

  GLuint ebo;
  glGenBuffers(1, &ebo);

  GLuint elements[] = {
      0, 1, 2, 1, 2, 3,
      4, 5, 6, 5, 6, 7,
  };

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  GLuint posAttrib = glGetAttribLocation(programObject, "position");
  glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(posAttrib);

  // transform for 2D
  GLfloat move[] = {
      1.0, 0.0f, 0.0f, 0.0,
      0.0f, 1.0, 0.0f, 0.0,
      0.0f, 0.0f, 1.0, 0.0f,
      100, 100, 0.0f, 1.0f,
  };

  GLint transformLocation = glGetUniformLocation(programObject, "move");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, move);

}

void Gl::resize(int width, int height)
{
  // transform for 2D
  GLfloat transform[] = {
      2.0f/(float)width, 0.0f, 0.0f, 0.0,
      0.0f, 2.0f/(float)height, 0.0f, 0.0,
      0.0f, 0.0f, 2.0f, 0.0f,
      -1.0f, -1.0f, 0.0f, 1.0f,
  };

  glUseProgram(programObject);

  GLint transformLocation = glGetUniformLocation(programObject, "transform");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);

  glUseProgram(circleProgram);

  transformLocation = glGetUniformLocation(circleProgram, "transform");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);
}

void drawCircle(int n, int s)
{
  glDrawArrays(GL_TRIANGLE_FAN, n, s);
}

void Gl::render(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(vao1);
  glUseProgram(programObject);

  glBindTexture( GL_TEXTURE_2D, mTextureID );
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

  glUseProgram(circleProgram);
  glBindVertexArray(vao2);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // update buffer

  int i = 0;
  for (std::shared_ptr<Circle> circle : world->circles)
    {
      float vertices[100];
      circle->generateVertices(20, vertices);
      glBufferSubData(GL_ARRAY_BUFFER, i*20*sizeof(GLfloat), 20*sizeof(GLfloat), vertices);
      glDrawArrays(GL_TRIANGLE_FAN, i*10, 10);
      i++;
    }
}

void Gl::linkProgram(GLuint program)
{
  glLinkProgram(program);

  GLint linked;

  glGetProgramiv(program, GL_LINK_STATUS, &linked);

  if (linked)
  {
      std::cout << "linked" << std::endl;
  }
  else
  {
      std::cout << "not linked" << std::endl;
      GLchar *info_log;
      int n;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &n);
      info_log = (char*)malloc(n);
      glGetProgramInfoLog(program, n, &n, info_log);
      std::cout << info_log << std::endl;
      free(info_log);
  }
}

GLuint Gl::fileToShader(GLenum type, const GLchar *filename)
{
  SDL_RWops* file = SDL_RWFromFile(filename, "r");

  GLuint shader = 0;

  if (file != NULL)
  {
    Uint8 buf[300];
    int i;
    for (i=0; i<300; i++)
    {
      buf[i] = 0;
    }
    SDL_RWread(file, buf, sizeof (buf), 1);
    SDL_RWclose(file);
    shader = compileShader(type, (GLchar*)buf);
  }
  else
  {
    std::cout << "file not found" << std::endl;
  }

  return shader;

}


GLuint Gl::compileShader(GLenum type, const GLchar *source)
{
    GLuint shaderObject = glCreateShader(type);

    glShaderSource(shaderObject, 1, &source, NULL);

    glCompileShader(shaderObject);

    GLint compiled;

    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compiled);
    if (compiled)
    {
        std::cout << "compiled shader\n";
    }
    else
    {
        std::cout << "not compiled shader\n";
        GLchar *info_log;
        int n;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &n);
        info_log = (char*)malloc(n);
        glGetShaderInfoLog(shaderObject, n, &n, info_log);
        std::cout << info_log << "\n";
        free(info_log);
    }

    return shaderObject;
}
