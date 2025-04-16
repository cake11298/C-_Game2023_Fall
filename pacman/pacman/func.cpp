﻿#pragma once
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

#include "func.h"

static bool replay = false; //check if starts a new game
static bool over = true; //check for the game to be over
static float squareSize = 50.0; //size of one square on the game
static float xIncrement = 0; // x movement on pacman
static float yIncrement = 0; // y movement on pacman
static int rotation = 0; // orientation of pacman
float* monster1 = new float[3]{ 10.5, 8.5, 1.0 }; //coordinates and direction of first monster
/*
float* monster2 = new float[3]{ 13.5, 1.5, 2.0 }; //coordinates and direction of second monster
float* monster3 = new float[3]{ 4.5, 6.5, 3.0 }; //coordinates and direction of third monster
float* monster4 = new float[3]{ 2.5, 13.5, 4.0 }; //coordinates and direction of fourth monster 
*/
static vector<int> border = { 0, 0, 15, 1, 15, 15, 14, 1, 0, 14, 15, 15, 1, 14, 0, 0 }; // coordinates of the border walls

// coordinates of the obstacles (divided into 3 for clarity)
static vector<int> obstaclesTop = { 2, 2, 3, 6, 3, 6, 4, 5, 4, 2, 5, 4, 5, 3, 6, 5, 6, 1, 9, 2, 7, 2, 8, 5, 9, 5, 10, 3, 10, 4, 11, 2, 11, 5, 12, 6, 12, 6, 13, 2 };
static vector<int> obstaclesMiddle = { 2, 9, 3, 7, 3, 7, 4, 8, 4, 9, 5, 11, 5, 6, 6, 10, 6, 10, 7, 8, 7, 8, 8, 9, 6, 7, 7, 6, 8, 6, 9, 7, 10, 6, 9, 10, 9, 10, 8, 8, 11, 9, 10, 11, 11, 8, 12, 7, 12, 7, 13, 9 };
static vector<int> obstaclesBottom = { 2, 10, 3, 13, 3, 13, 4, 12, 5, 12, 6, 13, 6, 13, 7, 11, 8, 11, 9, 13, 9, 13, 10, 12, 11, 12, 12, 13, 12, 13, 13, 10 };
static deque<float> food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
static vector<vector<bool>> bitmap; // 2d image of which squares are blocked and which are clear for pacman to move in
bool* keyStates = new bool[256];	// record of all keys pressed
int points = 0;						// total points collected
WSADATA wsa;
SOCKET s;
struct sockaddr_in server;
char buf[BUFLEN];
int identity = 0;
string idText = "";

// Initializes the game with the appropiate information
void init(void)
{

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	memset((char*)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	inet_pton(AF_INET, "10.33.7.9", &(server.sin_addr.s_addr));
	u_long mode = 1;
	ioctlsocket(s, FIONBIO, &mode);
	string now = "Ready to Play";
	sendto(s, now.data(), strlen(now.data()), 0, (struct sockaddr*)&server, sizeof(server));
	while (true) {
		char recvBuffer[BUFLEN];
		int recvLen;
		fd_set readfds;
		struct timeval tv;

		tv.tv_sec = 0;
		tv.tv_usec = 800;

		FD_ZERO(&readfds);
		FD_SET(s, &readfds);

		int selectResult = select(s + 1, &readfds, nullptr, nullptr, &tv);
		if (selectResult > 0) {
			if (FD_ISSET(s, &readfds)) {
				recvLen = recvfrom(s, recvBuffer, BUFLEN, 0, nullptr, nullptr);
				if (recvLen > 0) {
					recvBuffer[recvLen] = '\0';
					string receivedData(recvBuffer);
					string searchStr = "You can start ";
					size_t found = receivedData.find(searchStr);
					if (found != string::npos) {
						string identityStr = receivedData.substr(found + searchStr.length());
						identity = stoi(identityStr);
						cout << "Identity: " << identity << '\n';
						break;
					}
				}
			}
		}
	}
	// clear screen
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	// reset all keys
	over = false;
	replay = true;
	resetGame();
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}
	// fill the bitmap with the obstacles
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true });
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true });
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true });
	bitmap.push_back({ true, true, true, true, true, false, false, false, true, false, false, false, false, false, true });
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true });
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
}
void drawScore(int score) {
	glColor3f(0.5, 0.5, 1.0);  // Set color to white
	glRasterPos2f(760, 100);  // Set position to top left corner

	std::string scoreText = "Pacman Score: " + std::to_string(score);
	for (char c : scoreText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
	glColor3f(0.5, 0.5, 1.0);  // Set color to white
	glRasterPos2f(760, 150);  // Set position to top left corner
	if (identity == 1) {
		idText = "Identity : Pacman";
	}
	else if (identity == 2) {
		idText = "Identity : Monster 1";
	}
	else if (identity == 3) {
		idText = "Identity : Monster 2";
	}
	else if (identity == 4) {
		idText = "Identity : Monster 3";
	}
	else if (identity == 5) {
		idText = "Identity : Monster 4";
	}
	else if (identity == 6) {
		idText = "Identity : Pacman mate";
	}

	for (char c : idText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}
// Method to draw the obstacle course and the walls
void drawLaberynth()
{
	glColor3f(1.0, 1.0, 1.0);
	// Border
	for (int i = 0; i < border.size(); i = i + 4)
	{
		glRectf(border.at(i) * squareSize, border.at(i + 1) * squareSize, border.at(i + 2) * squareSize, border.at(i + 3) * squareSize);
	}

	// Obstacles
	for (int j = 0; j < obstaclesBottom.size(); j = j + 4)
	{
		glRectf(obstaclesBottom.at(j) * squareSize, obstaclesBottom.at(j + 1) * squareSize, obstaclesBottom.at(j + 2) * squareSize, obstaclesBottom.at(j + 3) * squareSize);
	}
	for (int k = 0; k < obstaclesMiddle.size(); k = k + 4)
	{
		glRectf(obstaclesMiddle.at(k) * squareSize, obstaclesMiddle.at(k + 1) * squareSize, obstaclesMiddle.at(k + 2) * squareSize, obstaclesMiddle.at(k + 3) * squareSize);
	}
	for (int p = 0; p < obstaclesTop.size(); p = p + 4)
	{
		glRectf(obstaclesTop.at(p) * squareSize, obstaclesTop.at(p + 1) * squareSize, obstaclesTop.at(p + 2) * squareSize, obstaclesTop.at(p + 3) * squareSize);
	}
	drawScore(points);  // Replace your_score_variable with your actual score variable
}

// Method to check if the food has been eaten
bool foodEaten(int x, int y, float pacmanX, float pacmanY)
{
	if (x >= pacmanX - 16.0 * cos(359 * M_PI / 180.0) && x <= pacmanX + 16.0 * cos(359 * M_PI / 180.0))
	{
		if (y >= pacmanY - 16.0 * cos(359 * M_PI / 180.0) && y <= pacmanY + 16.0 * cos(359 * M_PI / 180.0))
		{
			return true;
		}
	}
	return false;
}

// Method to draw all the food left and delete the ate one
void drawFood(float pacmanX, float pacmanY) {
	deque<float> temp;
	// check if the food has not been eaten
	for (int i = 0; i < food.size(); i = i + 2)
	{
		if (!foodEaten(food.at(i) * squareSize, food.at(i + 1) * squareSize, pacmanX, pacmanY))
		{
			temp.push_back(food.at(i));
			temp.push_back(food.at(i + 1));
		}
		else
		{
			points++;
		}
	}
	food.swap(temp);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	// draw all the food avilable
	for (int j = 0; j < food.size(); j = j + 2)
	{
		glVertex2f(food.at(j) * squareSize, food.at(j + 1) * squareSize);
	}
	glEnd();
}

void sendData(int s, const std::string& message, sockaddr_in& server) {
	sendto(s, message.data(), strlen(message.data()), 0, (struct sockaddr*)&server, sizeof(server));
}

// Method to draw the pacman character through consicutive circle algorithm
void drawPacman(float positionX, float positionY, float rotation)
{
	int x, y;
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	for (int k = 0; k < 32; k++)
	{
		x = (float)k / 2.0 * cos((30 + 90 * rotation) * M_PI / 180.0) + (positionX * squareSize);
		y = (float)k / 2.0 * sin((30 + 90 * rotation) * M_PI / 180.0) + (positionY * squareSize);
		for (int i = 30; i < 330; i++)
		{
			glVertex2f(x, y);
			x = (float)k / 2.0 * cos((i + 90 * rotation) * M_PI / 180.0) + (positionX * squareSize);
			y = (float)k / 2.0 * sin((i + 90 * rotation) * M_PI / 180.0) + (positionY * squareSize);
			glVertex2f(x, y);
		}
	}
	glEnd();
}

// Method to draw the monster character through consecutive circles algorithm
void drawMonster(float positionX, float positionY, float r, float g, float b)
{
	int x, y;

	glBegin(GL_LINES);
	glColor3f(r, g, b);
	// draw the head
	for (int k = 0; k < 32; k++)
	{
		x = (float)k / 2.0 * cos(360 * M_PI / 180.0) + (positionX * squareSize);
		y = (float)k / 2.0 * sin(360 * M_PI / 180.0) + (positionY * squareSize);
		for (int i = 180; i <= 360; i++)
		{
			glVertex2f(x, y);
			x = (float)k / 2.0 * cos(i * M_PI / 180.0) + (positionX * squareSize);
			y = (float)k / 2.0 * sin(i * M_PI / 180.0) + (positionY * squareSize);
			glVertex2f(x, y);
		}
	}
	glEnd();
	// draw body
	glRectf((positionX * squareSize) - 17, positionY * squareSize, (positionX * squareSize) + 15, (positionY * squareSize) + 15);
	glBegin(GL_POINTS);
	glColor3f(0, 0.2, 0.4);
	// draw eyes and legs
	glVertex2f((positionX * squareSize) - 11, (positionY * squareSize) + 14); // legs
	glVertex2f((positionX * squareSize) - 1, (positionY * squareSize) + 14);  // legs
	glVertex2f((positionX * squareSize) + 8, (positionY * squareSize) + 14);  // legs
	glVertex2f((positionX * squareSize) + 4, (positionY * squareSize) - 3);	  // eyes
	glVertex2f((positionX * squareSize) - 7, (positionY * squareSize) - 3);	  // eyes
	glEnd();
}



// Method to update the position of the monsters randomly
void updateMonster(float* monster, int id)
{
	// find the current position of the monster
	int x1Quadrant = (int)((monster[0] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
	int x2Quadrant = (int)((monster[0] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
	int y1Quadrant = (int)((monster[1] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
	int y2Quadrant = (int)((monster[1] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
	// move him acording to its direction until he hits an obstacle
	switch ((int)monster[2])
	{
	case 1:
		if (!bitmap.at(x1Quadrant).at((int)monster[1]))
		{
			monster[0] -= 2 / squareSize;
		}
		else
		{
			int current = monster[2];
			do
			{
				monster[2] = (rand() % 4) + 1;
			} while (current == (int)monster[2]);
		}
		break;
	case 2:
		if (!bitmap.at(x2Quadrant).at((int)monster[1]))
		{
			monster[0] += 2 / squareSize;
		}
		else
		{
			int current = monster[2];
			do
			{
				monster[2] = (rand() % 4) + 1;
			} while (current == (int)monster[2]);
		}
		break;
	case 3:
		if (!bitmap.at((int)monster[0]).at(y1Quadrant))
		{
			monster[1] -= 2 / squareSize;
		}
		else
		{
			int current = monster[2];
			do
			{
				monster[2] = (rand() % 4) + 1;
			} while (current == (int)monster[2]);
		}
		break;
	case 4:
		if (!bitmap.at((int)monster[0]).at(y2Quadrant))
		{
			monster[1] += 2 / squareSize;
		}
		else
		{
			int current = monster[2];
			do
			{
				monster[2] = (rand() % 4) + 1;
			} while (current == (int)monster[2]);
		}
		break;
	default:
		break;
	}
}

// Method to set the pressed key
void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
}

// Method to unset the released key
void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

// Method to reset all the variable necessaries to start the game again
void resetGame()
{
	over = false;
	xIncrement = 0;
	yIncrement = 0;
	rotation = 0;
	monster1 = new float[3]{ 10.5, 8.5, 1.0 };
	/*
	monster2 = new float[3]{ 13.5, 1.5, 2.0 };
	monster3 = new float[3]{ 4.5, 6.5, 3.0 };
	monster4 = new float[3]{ 2.5, 13.5, 4.0 };
	*/
	points = 0;
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}
	food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
}

string receiveData(int s) {
	char recvBuffer[BUFLEN];
	int recvLen;
	fd_set readfds;
	struct timeval tv;

	tv.tv_sec = 0;
	tv.tv_usec = 800;

	FD_ZERO(&readfds);
	FD_SET(s, &readfds);

	int selectResult = select(s + 1, &readfds, nullptr, nullptr, &tv);
	if (selectResult > 0) {
		if (FD_ISSET(s, &readfds)) {
			recvLen = recvfrom(s, recvBuffer, BUFLEN, 0, nullptr, nullptr);
			if (recvLen > 0) {
				recvBuffer[recvLen] = '\0';
				string receivedData(recvBuffer);
				if (!receivedData.empty()) {
					return receivedData;
				}
			}
		}
	}
	return "";
}

void updateEntity(float* entity, int id, bool* entityKeyStates)
{
	if (identity == 2) {
		// find the current position of the entity
		int x1Quadrant = (int)((entity[0] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
		int x2Quadrant = (int)((entity[0] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
		int y1Quadrant = (int)((entity[1] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
		int y2Quadrant = (int)((entity[1] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);

		// update according to keys pressed
		if (entityKeyStates['a'])
		{
			if (!bitmap.at(x1Quadrant).at((int)entity[1]))
			{
				entity[0] -= 1.5 / squareSize;
				entity[2] = 1; // rotation (if necessary)
			}
		}
		if (entityKeyStates['d'])
		{
			if (!bitmap.at(x2Quadrant).at((int)entity[1]))
			{
				entity[0] += 1.5 / squareSize;
				entity[2] = 2; // rotation (if necessary)
			}
		}
		if (entityKeyStates['w'])
		{
			if (!bitmap.at((int)entity[0]).at(y1Quadrant))
			{
				entity[1] -= 1.5 / squareSize;
				entity[2] = 3; // rotation (if necessary)
			}
		}
		if (entityKeyStates['s'])
		{
			if (!bitmap.at((int)entity[0]).at(y2Quadrant))
			{
				entity[1] += 1.5 / squareSize;
				entity[2] = 4; // rotation (if necessary)
			}
		}
		if (keyStates[' '])
		{
			if (!replay && over)
			{
				resetGame();
				replay = true;
			}
			else if (replay && over)
			{
				replay = false;
			}
		}
	}
	string tmpx = to_string(entity[0]), tmpy = to_string(entity[1]);
	string message = "x : " + tmpx + " y : " + tmpy;
	sendData(s, message, server);
}

// Method to update the movement of the pacman according to the movement keys pressed
void keyOperations() {
	if (identity == 1) {
		// get current position
		float x = (1.5 + xIncrement) * squareSize;
		float y = (1.5 + yIncrement) * squareSize;
		// update according to keys pressed
		if (keyStates['a'])
		{
			if (identity == 1) {//pacman
				x -= 2;
				int x1Quadrant = (int)((x - 16.0 * cos(360 * M_PI / 180.0)) / squareSize);
				if (!bitmap.at(x1Quadrant).at((int)y / squareSize))
				{
					xIncrement -= 1.5 / squareSize;
					rotation = 2;
				}
			}

		}
		if (keyStates['d'])
		{
			if (identity == 1) {//pacman
				x += 2;
				int x2Quadrant = (int)((x + 16.0 * cos(360 * M_PI / 180.0)) / squareSize);
				if (!bitmap.at(x2Quadrant).at((int)y / squareSize))
				{
					xIncrement += 1.5 / squareSize;
					rotation = 0;
				}
			}
		}
		if (keyStates['w'])
		{
			if (identity == 1) {//pacman
				y -= 2;
				int y1Quadrant = (int)((y - 16.0 * cos(360 * M_PI / 180.0)) / squareSize);
				if (!bitmap.at((int)x / squareSize).at(y1Quadrant))
				{
					yIncrement -= 1.5 / squareSize;
					rotation = 3;
				}
			}
		}
		if (keyStates['s'])
		{
			if (identity == 1) {//pacman
				y += 2;
				int y2Quadrant = (int)((y + 16.0 * cos(360 * M_PI / 180.0)) / squareSize);
				if (!bitmap.at((int)x / squareSize).at(y2Quadrant))
				{
					yIncrement += 1.5 / squareSize;
					rotation = 1;
				}
			}
		}
		if (keyStates[' '])
		{
			if (!replay && over)
			{
				resetGame();
				replay = true;
			}
			else if (replay && over)
			{
				replay = false;
			}
		}
		string tmpx = to_string(x), tmpy = to_string(y);
		char rota = '0' + rotation;
		string message = "x : " + tmpx + " y : " + tmpy + " rotation : " + rota;
		sendData(s, message, server);
	}
}

// Method to check if the game is over
void gameOver()
{
	int pacmanX = (int)(1.5 + xIncrement);
	int pacmanY = (int)(1.5 + yIncrement);
	int monster1X = (int)(monster1[0]);
	int monster1Y = (int)(monster1[1]);
	/*
	int monster2X = (int)(monster2[0]);
	int monster2Y = (int)(monster2[1]);
	int monster3X = (int)(monster3[0]);
	int monster3Y = (int)(monster3[1]);
	int monster4X = (int)(monster4[0]);
	int monster4Y = (int)(monster4[1]);
	*/
	if (pacmanX == monster1X && pacmanY == monster1Y)
	{
		over = true;
	}
	/*
	if (pacmanX == monster2X && pacmanY == monster2Y)
	{
		over = true;
	}
	if (pacmanX == monster3X && pacmanY == monster3Y)
	{
		over = true;
	}
	if (pacmanX == monster4X && pacmanY == monster4Y)
	{
		over = true;
	}
	*/
	if (points == 106)
	{
		over = true;
	}
}

// Method to display the results of the game at the ends
void resultsDisplay() {
	if (points == 106)
	{
		// Won
		const char* message = "*************************************";
		glRasterPos2f(170, 250);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		if(identity == 1) message = "CONGRATULATIONS, YOU WON! ";
		else if(identity == 2) message = "PACMAN EAT ALL THE POINTS, YOU LOSS! ";
		glColor3f(1, 1, 1);
		glRasterPos2f(200, 300);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "*************************************";
		glRasterPos2f(170, 350);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	}
	else
	{
		const char* message = "*************************";
		glRasterPos2f(210, 250);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		if (identity == 2) message = "CONGRATULATIONS, YOU WON! ";
		else if (identity == 1) message = "YOU LOSS! ";
		glColor3f(1, 1, 1);
		glRasterPos2f(250, 300);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "*************************";
		glRasterPos2f(210, 350);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		if (identity == 1) {
			message = "You got: ";
			glRasterPos2f(260, 400);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
			string result = to_string(points);
			message = (const char*)result.c_str();
			glRasterPos2f(350, 400);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
			message = " points!";
			glRasterPos2f(385, 400);
		}
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "To start mode 1,please press the key \'z\',or press \'y\' to start mode 2.";
		glRasterPos2f(100, 550);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
	}
}

void welcomeScreen()
{
	glClearColor(0, 0.2, 0.4, 1.0);
	const char* message = "*************************************";
	glRasterPos2f(150, 200);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "PACMAN WITH MULTIPLAYER";
	glColor3f(1, 1, 1);
	glRasterPos2f(225, 250);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "*************************************";
	glRasterPos2f(150, 300);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To control Pacman use A to go right, D to go left, W to go up and S to go down.";
	glRasterPos2f(50, 400);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "*************************************";
	glRasterPos2f(150, 450);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To start mode 1,please press the key \'z\'";
	glRasterPos2f(150, 500);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To start mode 2,please press the key \'y\'";
	glRasterPos2f(150, 550);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To start mode 3,please press the key \'p\'";
	glRasterPos2f(150, 600);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To start mode 4,please press the key \'o\'";
	glRasterPos2f(150, 650);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To start mode 5,please press the key \'c\'";
	glRasterPos2f(150, 700);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
}

// Method to display the screen and its elements
void display()
{
	if (points == 1)
	{
		over = false;
	}
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);
	gameOver();
	if (replay)
	{
		if (!over) {
			drawLaberynth();
			drawFood((1.5 + xIncrement) * squareSize, (1.5 + yIncrement) * squareSize);
			if (identity == 1) {
				drawPacman(1.5 + xIncrement, 1.5 + yIncrement, rotation);
				string monsterlocation = receiveData(s);
				size_t xStart = monsterlocation.find("x : ");
				size_t yStart = monsterlocation.find(" y : ");
				if (xStart != string::npos && yStart != string::npos) {
					string xStr = monsterlocation.substr(xStart + 4, yStart - xStart - 4);
					string yStr = monsterlocation.substr(yStart + 5);
					monster1[0] = stof(xStr);
					monster1[1] = stof(yStr);
				}
				cout << "Here are monster location on Pacman host : " << monster1[0] << ' ' << monster1[1] << '\n';
				drawMonster(monster1[0], monster1[1], 0.0, 1.0, 1.0); // cyan
			}
			else if (identity == 2) {
				updateEntity(monster1, 1, keyStates);
				string pacmanlocation = receiveData(s);
				size_t xStart = pacmanlocation.find("x : ");
				size_t yStart = pacmanlocation.find(" y : ");
				size_t rotationStart = pacmanlocation.find("rotation : ");
				if (xStart != string::npos && yStart != string::npos && rotationStart != string::npos) {
					string xStr = pacmanlocation.substr(xStart + 4, yStart - xStart - 4);
					string yStr = pacmanlocation.substr(yStart + 5, rotationStart - yStart - 6); // 使用 " y : "後的第一個字符到 "rotation : "的最後一個字符
					string rotationStr = pacmanlocation.substr(rotationStart + 11);
					xIncrement = stof(xStr) / squareSize - 1.5;
					yIncrement = stof(yStr) / squareSize - 1.5;
					rotation = stoi(rotationStr);
				}
				cout << "Here are Pacman location on monster host : " << xIncrement << ' ' << yIncrement << '\n';
				drawMonster(monster1[0], monster1[1], 0.0, 1.0, 1.0); // cyan
				drawPacman(1.5 + xIncrement, 1.5 + yIncrement, rotation);
			}
		}

		else
		{
			resultsDisplay();
		}
	}
	else
	{
		welcomeScreen();
	}
	glutSwapBuffers();
}

// Methdo to reshape the game is the screen size changes
void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glOrtho(0, 1000, 1000, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}