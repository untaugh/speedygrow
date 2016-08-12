#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include "gl.hpp"

int main(int, char**){

	SDL_Window *mainwindow; /* Our window handle */
	SDL_GLContext maincontext; /* Our opengl context handle */

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mainwindow = SDL_CreateWindow("speedygrow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	maincontext = SDL_GL_CreateContext(mainwindow);

  SDL_GL_SetSwapInterval(1);

  Gl * gl = new Gl();
  gl->init();
  gl->resize(640,480);
  gl->render();

  SDL_GL_SwapWindow(mainwindow);
  SDL_Delay(2000);

	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}
