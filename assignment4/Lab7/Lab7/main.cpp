//FileName:		main.cpp
//Programmer:	Dan Cliburn
//Date:			4/1/2015
//Purpose:		This file defines the main() function for Lab 7.

#include "viewcontroller.h"
#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[])  //main() must take these parameters when using SDL
{


	Viewcontroller vc;
	cout << "created by: Keely Canniff, Darrel Holt, and Norlan Prudente \n";
	cout << " our 3D model is a skateboard, press the down arrow button to make the wheels spin! \n";
	system("pause");
	vc.run();

	system("pause");
	return 0;
}