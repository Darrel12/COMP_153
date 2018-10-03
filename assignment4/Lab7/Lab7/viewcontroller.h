//FileName:		viewcontroller.h
//Programmer:	Dan Cliburn
//Date:			4/1/2015
//Purpose:		This file defines the header for the Viewcontroller class

#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <SDL.h>
#include "model.h"

class Viewcontroller
{
	private:
		bool quit;

		//Variables to help control the mouse rotation 
		bool ROTATING;
		float baseX, baseY;
		float lastOffsetX, lastOffsetY;
		float yAngle;
		float xAngle;

		Model m;

		SDL_Window *window;
		SDL_GLContext ogl4context;

	public:
		Viewcontroller();

		bool init();  //initializes SDL, GLEW, and OpenGL
		void display();
		void run();
		bool handleEvents(SDL_Event *theEvent);
};

#endif