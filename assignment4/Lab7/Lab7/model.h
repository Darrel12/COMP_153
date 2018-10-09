//FileName:		model.h
//Programmer:	Dan Cliburn
//Date:			4/1/2015
//Purpose:		This file defines the header for the Model class.
//The "Model" is just what we want to render in our scene.
//The Model class is responsible for calling all of the OpenGL and GLEW functions.

#ifndef MODEL_H
#define MODEL_H

#include <glew.h> //glew.h is supposed to be included before gl.h.  To be safe, you can just include glew.h instead
#include <glm.hpp>
#include "texmodel.h"
#include "wheel.h"
using namespace glm;

class Model
{
	private:
		GLint PVM_matrixLoc;
		mat4 model_matrix;
		mat4 view_matrix;
		mat4 projection_matrix;

		TexModel tiger;
		TexModel pacific;
		TexModel topOfBoard;
		TexModel bottomOfBoard;
		TexModel leftSide;
		TexModel rightSide;
		TexModel leftCap;
		TexModel rightCap;
		TexModel leftWheelFront;
		wheel WheelLeftFrontCircle;
		wheel WheelRightFrontCircle;
		wheel WheelLeftBackCircle;
		wheel WheelRightBackCircle;






	public:
		Model();

		bool init();  //initializes OpenGL, GLEW, and the objects we want to draw
		void draw(float xAngle, float yAngle);  //renders the objects we want to draw
};

#endif