#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
int index_x[40], index_y[40];
int lengthOfSnake;
int value1 = 1;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

class game {
	int x, y, foodX, foodY, score;

	const int width = 20;
	const int height = 20;
public:
	game();
	void composeFrame();
	void input();
	void logic();
	~game() {};
};
game::game (void)
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}
void game:: composeFrame(void)
{
	system("cls"); //system("clear");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == foodY && j == foodX)
				cout << "*";
			else
			{
				bool print = false;
				for (int k = 0; k < lengthOfSnake; k++)
				{
					if (index_x[k] == j && index_y[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
	cout << "Press X to EXIT\n";
}
void game ::input(void)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void game:: logic(void)
{
	int prevX = index_x[0];
	int prevY = index_y[0];
	int prev2X, prev2Y;
	index_x[0] = x;
	index_y[0] = y;
	for (int i = 1; i < lengthOfSnake; i++)
	{
		prev2X = index_x[i];
		prev2Y = index_y[i];
		index_x[i] = prevX;
		index_y[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//	gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < lengthOfSnake; i++)
		if (index_x[i] == x && index_y[i] == y)
			gameOver = true;
	
	if (x == foodX && y == foodY)
	{
		
		score += value1;
		foodX = rand() % width;
		foodY = rand() % height;
		lengthOfSnake++;
		if (score % 10 == 0)
			value1++;
	}
}
int main()
{
	int temp1;
	game snake;
	while (!gameOver)
	{
		snake.composeFrame();
		snake.input();
		snake.logic();
		temp1 = value1 * 10;

		if (temp1 > 60)
			Sleep(5);
		else
			Sleep(100 - temp1);
	}
	return 0;
}