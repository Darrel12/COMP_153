#include "wheel.h"
#include "wheel.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int red = 2;
const int green = 0;
const int blue = 0;
const int alpha = 2;

const float PI = 3.14159;
const float radius = 2;
const float step = 15.0;


wheel::wheel()
{
	//spotList[5] = { -.8, -0.4, 0, .4, .8}; //list of location spots for coin to be
	srand(time(NULL));
	VAO = 0;
	//Buffer = 0;
	vertexNum = 0;
}
bool wheel::init() {

	randX = rand() % 4;     // v2 in the range 0 to 4
	randY = rand() % 4;     // v2 in the range 0 to 4
	xValue = spotList[randX];
	yValue = spotList[randY];
	glGenVertexArrays(1, &VAO);  //Create one vertex array object
	glBindVertexArray(VAO);

	//draw circle
	vertexNum = 0;
	//First specify the center point for our triangle fan
	vertices[vertexNum][0] = 0.0;
	vertices[vertexNum][1] = 0.0;
	vertices[vertexNum][2] = 0.5; //z value
	vertexNum++;
	//Now specify all of the points on the outer edge of our triangle strip
	for (float angle = 0; angle <= 360; angle += step)
	{
		vertices[vertexNum][0] = radius * cos((PI*angle) / 180.0);
		vertices[vertexNum][1] = radius * sin((PI*angle) / 180.0);
		vertices[vertexNum][2] = 0.5; //z value
		vertexNum++;
	}

	glGenBuffers(1, &Buffer); //Create a buffer object for the vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  //Do the shader plumbing here for this buffer
	glEnableVertexAttribArray(0);

	//Provide gray as the static vertex attribute value for the color 
	glVertexAttrib4f(1, 0.5, 0.5, 0.5, 1.0);

	return true;  //Everything got initialized





}

void wheel::draw() {
		//cout << randX;
		//glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		//glPointSize(0.1);
		//glLineWidth(0.1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertexNum);
		//glFlush();
}


wheel::~wheel()
{
}
