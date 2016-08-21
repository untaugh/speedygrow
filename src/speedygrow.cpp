#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include "gl.hpp"
#include <Box2D/Box2D.h>

int main(int, char**)
{
  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;
  
  SDL_Window *mainwindow;
  SDL_GLContext maincontext; 
  
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
  gl->resize(640/4,480/4);
  gl->render();

  SDL_GL_SwapWindow(mainwindow);

  bool quit = false;

  //Event handler
  SDL_Event e;
		
  SDL_StartTextInput();

  while(!quit)
    {
      //update world
      gl->world->world->Step(timeStep, velocityIterations, positionIterations);

      while( SDL_PollEvent( &e ) != 0 )
	{
	  if( e.type == SDL_QUIT )
	    {
	      quit = true;
	    }
	  else if( e.type == SDL_TEXTINPUT )
	    {
	      if (e.text.text[0] == 'q')
		{
		  quit = true;
		}
	    }
	}
      
      gl->render();
			
      SDL_GL_SwapWindow( mainwindow );
    }

  SDL_StopTextInput();
    
  SDL_GL_DeleteContext(maincontext);
  SDL_DestroyWindow(mainwindow);
  SDL_Quit();
  
  return 0;
}
