#include <winsock2.h>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <ws2tcpip.h>
#define _USE_MATH_DEFINES
#include <math.h>
// #include <opencv2/opencv.hpp> //opencv的頭文件
// using namespace cv;
using namespace std;
#pragma comment(lib, "ws2_32.lib") // Winsock Library

#define SERVER "10.33.7.9" // ipv4 address
#define BUFLEN 512		   // maximum buffer size
#define PORT 8080		   // port on which to send data
#include "func.h"


int main(int argc, char** argv)
{
	// initialize and create the screen
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1100, 900);
	glutInitWindowPosition(500, 50);
	glutCreateWindow("PACMAN");

	// define all the control functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	// run the game
	init();
	glutMainLoop();
	return 0;
}