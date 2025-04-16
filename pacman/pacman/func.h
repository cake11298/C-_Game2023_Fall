#pragma once
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
using namespace std;
#pragma comment(lib, "ws2_32.lib") // Winsock Library

#define SERVER "10.33.7.9"  // ipv4 address
#define BUFLEN 512  // maximum buffer size
#define PORT 8080  // port on which to send data


//Initializes the game with the appropiate information 
void init(void);

//Method to draw the obstacle course and the walls
void drawLaberynth();

//Method to check if the food has been eaten
bool foodEaten(int, int, float, float);

//Method to draw all the food left and delete the ate one
void drawFood(float, float);

//Method to draw the pacman character through consicutive circle algorithm
void drawPacman(float, float, float);

//Method to draw the monster character through consecutive circles algorithm
void drawMonster(float, float, float, float, float);

//Method to the position of the monsters randomly
void updateMonster(float*, int);

//Method to set the pressed key
void keyPressed(unsigned char, int, int);

//Method to unset the released key
void keyUp(unsigned char, int, int);

//Method to reset all the variable necessaries to start the game again
void resetGame();

//Method to the movement of the pacman according to the movement keys pressed
void keyOperations();

//Method to check if the game is over
void gameOver();

//Method to display the results of the game at the ends
void resultsDisplay();

//Method to display the starting instructions
void welcomeScreen();

//Method to display the screen and its elements
void display();

//Methdo to reshape the game is the screen size changes
void reshape(int, int);
