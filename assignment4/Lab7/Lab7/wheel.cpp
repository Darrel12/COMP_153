#include "wheel.h"
#include "wheel.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int red = 0;
const int green = 1;
const int blue = 2;
const int alpha = 3;
const GLuint NumVertices = 18;


wheel::wheel()
{
	VAO = 0;
}
bool wheel::init() {

	//Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "Error initializing GLEW: " << glewGetErrorString(err) << endl;
		return false;
	}

	glGenVertexArrays(1, &VAO);  //Create one vertex array object
	glBindVertexArray(VAO);

	int vertexNum;

	//First we'll pseudo randomly determine positions for the points.  
	//X values will be fixed, but y values will be random.
	//Note that even though I am using rand(), since I don't call 
	//srand(time(0)) in the program you will get the same set of 
	//vertices each time you run the program.
/*
	float xPos = -.85;
	int yPos;
	srand(time(0));
	for (vertexNum = 0; vertexNum < NumVertices; vertexNum++)
	{
		yPos = rand()%19 - 9;
		positions[vertexNum][0] = cos(xPos);  //x value for vertex
		positions[vertexNum][1] = sin(yPos / 10.0);  //y value for vertex
		xPos += .1;
	}
*/
//circle
	float radius = 1.0;
	double step = 360.0 / (NumVertices - 2);
	const float PI = 3.14159;
	vertexNum = 0;
	positions[vertexNum][0] = 0.0;  //x value for vertex
	positions[vertexNum][1] = 0.0;  //y value for vertex
	vertexNum++;
	for (double angle = 0; angle <= 360; angle += step)
	{
		positions[vertexNum][0] = radius * cos((PI*angle) / 180.0);  //x value for vertex
		positions[vertexNum][1] = radius * sin((PI*angle) / 180.0);  //y value for vertex
		vertexNum++;
	}


	int R, G, B;
	//Assign the colors
	for (vertexNum = 0; vertexNum < NumVertices; vertexNum++)
	{
		R = rand() % 256;
		G = rand() % 256;
		B = rand() % 256;
		colors[vertexNum][red] = R / 256.0;
		colors[vertexNum][green] = G / 256.0;
		colors[vertexNum][blue] = B / 256.0;
		colors[vertexNum][alpha] = 1.0;
	}

	glGenBuffers(2, Buffers); //Create two buffer objects, one for vertex positions and one for vertex colors
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);  //Buffers[0] will be the position for each vertex
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);  //Do the shader plumbing here for this buffer
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);  //Buffers[1] will be the color for each vertex
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);  //Do the shader plumbing here for this buffer
	glEnableVertexAttribArray(1);


	return true;  //Everything got initialized





}

void wheel::draw() {
	//glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAO);

	//TODO: Try using the following OpenGL primitive mode types with the vertices:
	//GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES, GL_TRIANGLE_STRIP
	//TODO: Also try using glPointSize(GLfloat size) and glLineWidth(GLfloat width) with
	//point and line modes (respectively) and with various parameters to see their effects.
	glPointSize(1.0);
	glLineWidth(1.0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);
	//glFlush();
}


wheel::~wheel()
{
}
