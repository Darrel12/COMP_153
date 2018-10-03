//FileName:		model.cpp
//Programmer:	Dan Cliburn
//Date:			4/1/2015
//Purpose:		Defines the methods for the Model class.
//The init() method needs to set up OpenGL and GLEW and prepare all objects to be rendered.
//The draw() method needs to render all objects in the scene.
//keely test commit
#include <glew.h> //glew.h is supposed to be included before gl.h.  To be safe, you can just include glew.h instead
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "model.h"
#include "LoadShaders.h"
#include <iostream>
using namespace std;
using namespace glm;

Model::Model()
{
	PVM_matrixLoc = 0;
	model_matrix = mat4(1.0);
	view_matrix = mat4(1.0);
	projection_matrix = mat4(1.0);
}

//init() does all of the OpenGL and GLEW initialization.  
//You also want to call the init() methods in here for any of your other classes that use OpenGL 
bool Model::init()
{
	//Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "Error initializing GLEW: " << glewGetErrorString(err) << endl;
		return false;
	}

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glEnable(GL_DEPTH_TEST);

	//The following code was adapted from the OpenGL 4.0 Shading Language Cookbook, by David Wolff
	//to provide information about the hardware and supported versions of OpenGL and GLSL. 
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "GL Vendor: " << vendor << endl;
	cout << "GL Renderer: " << renderer << endl;
	cout << "GL Version: " << version << endl;
	cout << "GLSL Version: " << glslVersion << endl << endl;

	//Finally, we need to load the shaders. I am using the LoadShaders() function written  
	//by the authors of the OpenGL Programming Guide (8th edition).
	ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "shader.vert" },
			{ GL_FRAGMENT_SHADER, "shader.frag" },
			{ GL_NONE, NULL }
	};
	GLuint program;
	if ((program = LoadShaders(shaders)) == 0)
	{
		cout << "Error Loading Shaders" << endl;
		return false;
	}
	glUseProgram(program);

	//Now initialize all of our models
	GLfloat green[4] = { 0.0, 1.0, 0.0, 1.0 };
	tiger.init("images/tiger.bmp", green);
	pacific.init("images/pacific.bmp", green);

	//Find the location of the PVM_matrix in the shader
	PVM_matrixLoc = glGetUniformLocation(program, "PVM_matrix");

	//Since the projection and view orientation matrices will not change during the program we will calculate them here
	projection_matrix = frustum(-0.1, 0.1, -0.1, 0.1, 0.1, 20.0);
	vec3 eye = vec3(1.5, 1.5, 1.5);
	vec3 aim = vec3(0.0, 0.0, 0.0);
	vec3 up = vec3(0.0, 1.0, 0.0);
	view_matrix = lookAt(eye, aim, up);

	return true;  //Everything got initialized
}

//draw() explains how to render your model
void Model::draw(float xAngle, float yAngle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculate the rotation based on the xAngle and yAngle variables
	model_matrix = rotate(mat4(1.0), (float)(yAngle*(3.14159 / 180.0)), vec3(0.0f, 1.0f, 0.0f));
	model_matrix = rotate(model_matrix, (float)(xAngle*(3.14159 / 180.0)), vec3(1.0f, 0.0f, 0.0f));

	//Remember that the matrices are applied to vertices in the opposite order
	//in which they are specified below (i.e. model_matrix is applied first)
	mat4 PVMmatrix = projection_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(PVM_matrixLoc, 1, GL_FALSE, value_ptr(PVMmatrix));
	tiger.draw();

	model_matrix = translate(model_matrix, vec3(0.0f, -1.1f, 0.5f));
	model_matrix = rotate(model_matrix, (float)(-90.0*(3.14159/180.0)), vec3(1.0f, 0.0f, 0.0f));
	PVMmatrix = projection_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(PVM_matrixLoc, 1, GL_FALSE, value_ptr(PVMmatrix));
	pacific.draw();

	glFlush();
}