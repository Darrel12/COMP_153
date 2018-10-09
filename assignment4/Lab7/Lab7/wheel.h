#pragma once

#ifndef WHEEL_H
#define WHEEL_H

#include <glew.h>  //glew.h is supposed to be included before gl.h.  To be safe, you can just include glew.h instead
using namespace std;

const GLuint theNumVertices = 20;
class wheel
{
private:
	GLfloat positions[theNumVertices][2];  //each vertex has an x and a y value
	GLfloat colors[theNumVertices][4]; //each color has a red, green, blue, and alpha value 
	GLuint VAO;
	GLfloat vertices[30][3];  //each vertex has an x, y, and z value
	GLuint Buffers[2];  //We'll need one buffer for the vertices and one for the colors
	//GLfloat vertices[40][2];  //each vertex has an x and a y value
	//GLuint Buffer;  //We'll need one buffer for the vertices and one for the colors
	int vertexNum; //for drawing
	GLuint Buffer; // for drawing
	float xValue;
	float yValue;
	float spotList[5] = { -0.8F, -0.4F, 0.0F, 0.4F, 0.8F }; //locations for the coin to possibly go
	//float spotList[]
	bool drawMe;
	int randX;
	int randY;

public:
	wheel();

	bool init();  //initializes the model
	void draw();  //renders the model
	float getX(); //get the x value
	/*float getY(); //get the y value
	void setX(float x); //set the x value
	void setY(float y); //se the y value
	void DontDrawMe(); // dont draw coin after being picked up
	void ResetXAndY(); //incase the coin is place ontop of antoher, reset the x and y values
	void setDrawMeToTrue(); // draw coin after reset */
	~wheel();
};
#endif
