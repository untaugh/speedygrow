#include "gl.hpp"
#include <SDL.h>
#include <iostream>

Gl::Gl()
{
  GLenum err = glewInit();
  if (err != GLEW_OK)
    exit(1);
  if (!GLEW_VERSION_2_1)
    exit(1);

  SDL_RWops* file = SDL_RWFromFile("src/vertex.glsl", "r");

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
    vertexShader = compileShader(GL_VERTEX_SHADER, (GLchar*)buf);
  }
  else
  {
    std::cout << "file not found" << std::endl;
  }

  file = SDL_RWFromFile("src/fragment.glsl", "r");

  if (file != NULL)
  {
    Uint8 buf[256];
    int i;
    for (i=0; i<256; i++)
    {
      buf[i] = 0;
    }
    SDL_RWread(file, buf, sizeof (buf), 1);
    SDL_RWclose(file);
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, (GLchar*)buf);
  }
  else
  {
    std::cout << "file not found" << std::endl;
  }
}

void Gl::init(void)
{
  glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //texture = new QOpenGLTexture( QImage( ":/Textures/alien.png" ) );

  glClearColor(1.0, 0.9, 1.0, 1.0);

  programObject = glCreateProgram();
  glAttachShader(programObject, vertexShader);
  glAttachShader(programObject, fragmentShader);

  glLinkProgram(programObject);

  GLint linked;

  glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

  if (linked)
  {
      std::cout << "linked\n";
  }
  else
  {
      std::cout << "not linked\n";
      GLchar *info_log;
      int n;
      glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &n);
      info_log = (char*)malloc(n);
      glGetProgramInfoLog(programObject, n, &n, info_log);
      std::cout << info_log << "\n";
      free(info_log);
  }

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

  GLuint vbo;

  // create buffers
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
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

  //
  // // transform for 2D
  // GLfloat move[] = {
  //     1.0, 0.0f, 0.0f, 0.0,
  //     0.0f, 1.0, 0.0f, 0.0,
  //     0.0f, 0.0f, 1.0, 0.0f,
  //     100, 100, 0.0f, 1.0f,
  // };
  //
  // GLint transformLocation = glGetUniformLocation(programObject, "move");
  // glUniformMatrix4fv(transformLocation, 1, GL_FALSE, move);

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

  GLint transformLocation = glGetUniformLocation(programObject, "transform");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);
}

void Gl::render(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
   //glMatrixMode( GL_MODELVIEW );
   //glLoadIdentity();
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
  // glDrawArrays( GL_TRIANGLES, 0, 3);
  //  glBegin( GL_QUADS );
  //   glColor3f( 0.f, 1.f, 1.f );
  //  glVertex2f( -0.5f, -0.5f );
  //  glVertex2f( 50.5f, -0.5f );
  //  glVertex2f( 50.5f, 0.5f );
  //  glVertex2f( -0.5f, 0.5f );
  //  glEnd();
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
