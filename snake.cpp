#include <iostream>
using namespace std;
#include <Windows.h>
#include <conio.h>

//Global Variables:
bool GameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


// Set Up the Game.
void SetUp()
{
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
}

// Create the map for the game.
void draw()
{
	system("cls");
	for (int i = 0; i <= width; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}

			}
				
		}
		cout << endl;
	}
	for (int i = 0; i <= width; i++) {
		cout << "#";
	}
	cout << endl << "Score: " << score;
}

// Provide controls to the game.
void input()
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			GameOver = true;
			break;
		}
	}
}

// The rules and settings for the game.
void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch(dir)
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	default:
		break;
	}

	// Snake die if wall is hitted:
	//if (x > width-2 || x < 0 || y >= height || y < 0) {
	//	GameOver = true;
	//}

	// Allow the snake go through walls:
	if (x >= width-1) x = 0; else if (x < 0) x = width - 2;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;


	// Snake die if tail is hitted:
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			GameOver = true;
		}
	}
	
	// Fruit spawn point, score, and tail size
	if (x == fruitX && y == fruitY) {
		score++;
		nTail++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}

}

int main() {

	SetUp();
	srand(time(0));
	while (!GameOver) {
		draw();
		input();
		logic();
		Sleep(130);  // Adjust the speed of the game.
	}
	return 0;
}
