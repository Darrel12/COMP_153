//FileName:		texmodel.cpp
//Programmer:	Dan Cliburn
//Date:			9/9/2014
//Purpose:		To define the model that we want to render in our OpenGL program.

#include <glew.h>  //glew.h is supposed to be included before gl.h.  To be safe, you can just include glew.h instead
#include "texmodel.h"
#include "texture.h"
#include <iostream>
#include <string>
using namespace std;

TexModel::TexModel()
{
	texID = 0;
}

void TexModel::buildMipMaps()
{
	glBindTexture(GL_TEXTURE_2D, texID);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void TexModel::defineTexCoords()
{
	//Texture Coordinates
	tex_coords[0][0] = 0.0; //upper-left
	tex_coords[0][1] = 1.0;
	tex_coords[1][0] = 0.0; //lower-left
	tex_coords[1][1] = 0.0;
	tex_coords[2][0] = 1.0; //upper-right
	tex_coords[2][1] = 1.0;
	tex_coords[3][0] = 1.0; //lower-right
	tex_coords[3][1] = 0.0;
}

//init() does all of the OpenGL initialization for your model(s)
bool TexModel::init(string texFileName, const GLfloat *c) //c can be an array with RGBA values for the color of the quad
{
	glGenVertexArrays(1, &VAO);  //Create one vertex array object
	glBindVertexArray(VAO);

	defineVertexPositions();  //Call the method inherited from Quad to set up the vertex positions
	defineTexCoords(); //Call the method up above to set up the texture coordinates

	glGenBuffers(2, Buffers); //Create two buffer objects, one for vertex positions and one for texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);  //Buffers[0] will be the position for each vertex
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  //Do the shader plumbing here for this buffer
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);  //Buffers[1] will be the texture coordinates
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);  //Do the shader plumbing here for this buffer
	glEnableVertexAttribArray(1);
	
	defineVerticeColor(c); //Call the method inherited from Quad to set up the quad's color using a static vertex attribute

	//Now we need to load our texture
	initTexture(texFileName);

	initialized = true;
	return true;  //Everything got initialized
}

void TexModel::initTexture(string texFileName)
{
	Texture t(texFileName, true); cout << endl;

	glGenTextures(1, &texID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, t.width(), t.height());
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, t.width(), t.height(), GL_RGB, GL_UNSIGNED_BYTE, t.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

//draw() explains how to render your model
void TexModel::draw()
{
	if (initialized == false)
	{
		cout << "ERROR: Cannot render a TexModel object before it has been initialized." << endl;
		return;
	}

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID); //Bind the texture with the ID of texID to this VAO
	//NOTE that we need to make sure that the correct texture is bound for the appropriate object before every draw.
	//Otherwise, the last texture loaded will be applied to every object in the scene since OpenGL is a state machine.

	glVertexAttrib4f(2, color[0], color[1], color[2], color[3]);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}