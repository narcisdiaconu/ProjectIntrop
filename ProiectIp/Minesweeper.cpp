#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
using namespace std;
int grid[50][50], clicked[50][50];
void matrixGeneration(int grid[50][50], int height, int width, int bombs) {
	int bomsOnMap = 0;
	grid[-1][-1] = 201;
	grid[-1][width] = 187;
	grid[height][-1] = 200;
	grid[height][width] = 188;
	for (int i = 0; i < width; i++){
		grid[-1][i] = 205;
		grid[height][i] = 205;
	}
	for (int i = 0; i < height; i++) {
		grid[i][-1] = 186;
		grid[i][width] = 186;
	}
	while (bomsOnMap < bombs) {
		int x, y;
		x = rand() % height;
		y = rand() % width;
		if (grid[x][y] != -1) {
			grid[x][y] = -1;
			bomsOnMap++;
		}
	}
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (grid[i][j] != -1) {
				if (grid[i - 1][j] == -1)
					grid[i][j]++;
				if (grid[i - 1][j - 1] == -1)
					grid[i][j]++;
				if (grid[i - 1][j + 1] == -1)
					grid[i][j]++;
				if (grid[i][j - 1] == -1)
					grid[i][j]++;
				if (grid[i][j + 1] == -1)
					grid[i][j]++;
				if (grid[i + 1][j - 1] == -1)
					grid[i][j]++;
				if (grid[i + 1][j] == -1)
					grid[i][j]++;
				if (grid[i + 1][j + 1] == -1)
					grid[i][j]++;
			}
}

void afisare(int grid[50][50],int clicked[50][50], int height, int width)
{	
	for (int i = -1; i <= height; i++) {
		for (int j = -1; j <= width; j++)
			if (i == -1 || j == -1 || i == height || j == width) {
				cout << char(grid[i][j]);
				if (i == -1 && grid[i][j] != 187 && grid[i][j] != 201 && j != width - 1)
					cout << char(209);
				else
					if (i == height && grid[i][j] != 200 && grid[i][j] != 188 && j != width - 1)
						cout << char(207);
			}
			else
				if(clicked[i][j]==2)
					if (j == width - 1)
						cout << "?";
					else
						cout << "?" << char(179);
				else
					if (clicked[i][j] == -1)
						if (j == width - 1)
							cout << char(178);
						else
							cout << char(178) << char(179);
				else	
					if (clicked[i][j] == 1)
						if (j == width- 1)
							cout << grid[i][j];
						else
							cout << grid[i][j] << char(179);
					else
						if (j == width - 1)
							cout << char(178);
						else
							cout << char(178) << char(179);
		cout << endl;
		if (i != -1 && i != height - 1 && i != height) {
			cout << char(199);
			for (int k = 0; k < width-1; k++)
				cout << char(196) << char(197);
			cout <<char(196)<< char(182) << endl;
		}
	}
}

void modify(short x, short y, int height, int width) {
	if (grid[x][y] == 0)
	{
		clicked[x][y] = 1;
		if (x > 0 && clicked[x - 1][y] == 0)
			modify(x - 1, y, height, width);
		if (x < height && clicked[x + 1][y] == 0)
			modify(x + 1, y, height, width);
		if (y > 0 && clicked[x][y - 1] == 0)
			modify(x, y - 1, height, width);
		if (y < width&&clicked[x][y + 1] == 0)
			modify(x, y + 1, height, width);
	}
	else
		if (grid[x][y] != -1)
			clicked[x][y] = 1;
}

void click(short &x, short &y, int &type){
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRecord;
	DWORD Events;
	COORD coord;
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hout, &cci);
	DWORD dwPreviousMode = 0;
	GetConsoleMode(hin, &dwPreviousMode);
	DWORD dwNewMode = dwPreviousMode | ENABLE_MOUSE_INPUT;
	dwNewMode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hin, dwNewMode | ENABLE_EXTENDED_FLAGS);
	bool clickPressed = false;
	while (!clickPressed) {
		ReadConsoleInput(hin, &inputRecord, 1, &Events);
		if (inputRecord.EventType == MOUSE_EVENT) {
			if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				x = inputRecord.Event.MouseEvent.dwMousePosition.X;
				y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
				type = 1;
				clickPressed = true;
			}
			else
				if (inputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
					x = inputRecord.Event.MouseEvent.dwMousePosition.X;
					y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
					type = 2;
					clickPressed = true;
				}
				else;
		}
	}
	SetConsoleMode(hin, dwPreviousMode | ENABLE_EXTENDED_FLAGS);
}

void mainMenu() {
	cout << char(201);
	for (int i = 0; i < 41; i++)
		cout << char(205);
	cout << char(187) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "     *       * ***** *     *  *    *     " << char(186) << endl;
	cout << char(186) << "     * *   * * *     * *   *  *    *     " << char(186) << endl;
	cout << char(186) << "     *  * *  * ***   *  *  *  *    *     " << char(186) << endl;
	cout << char(186) << "     *   *   * *     *   * *  *    *     " << char(186) << endl;
	cout << char(186) << "     *       * ***** *     *  ******     " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "               START GAME                " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "               HOW TO PLAY               " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "               EXIT                      " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(200);
	for (int i = 0; i < 41; i++)
		cout << char(205);
	cout << char(188) << endl;
}

void playMenu() {
	cout << char(201);
	for (int i = 0; i < 41; i++)
		cout << char(205);
	cout << char(187) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "            CHOOSE DIFICULTY:            " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "            EASY                         " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "            MEDIUM                       " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "            HARD                         " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(186) << "            CUSTOM                       " << char(186) << endl;
	cout << char(186) << "                                         " << char(186) << endl;
	cout << char(200);
	for (int i = 0; i < 41; i++)
		cout << char(205);
	cout << char(188) << endl;
}

int menuSelection(short x, short y) {
	if (x >= 16 && x <= 25 && y == 9)
		return 1;
	else
		if (x >= 16 && x >= 26 && y == 11)
			return 2;
		else
			if (x >= 16 && x <= 19 && y == 13)
				return 3;
	return 0;
}

void howtoplayMenu() {

}

int dificultySelection(short x, short y) {
	if (x >= 13 && x <= 16 && y == 4)
		return 1;
	else
		if (x >= 13 && x <= 18 && y == 6)
			return 2;
		else
			if (x >= 13 && x <= 16 && y == 8)
				return 3;
			else
				if (x >= 13 && x <= 18 && y == 10)
					return 4;
	return 0;
}

int main() {
	srand(time(NULL));
	bool exitGame = false;
	short mouseX, mouseY;
	int mouseType;
	while (!exitGame) {
		mainMenu();
		click(mouseX, mouseY, mouseType);
		int menuSelect = menuSelection(mouseX, mouseY);
		while (menuSelect == 0 || mouseType == 2) {
			system("cls");
			mainMenu();
			cout << mouseX << " " << mouseY;
			click(mouseX, mouseY, mouseType);
			menuSelect = menuSelection(mouseX, mouseY);
		}
		switch(menuSelect){
		case 1:
		{
			system("cls");
			playMenu();
			click(mouseX, mouseY, mouseType);
			int difSelect = dificultySelection(mouseX, mouseY);
			while (difSelect == 0 || mouseType == 2) {
				system("cls");
				playMenu();
				cout << mouseX << " " << mouseY;
				click(mouseX, mouseY, mouseType);
				difSelect = dificultySelection(mouseX, mouseY);
			}
			switch (difSelect) {
			case 1: {
				system("cls");
				
			}
				break;
			case 2: {
				system("cls");
				
			}
				break;
			case 3: {
				system("cls");
				
			}
				break;
			case 4: {
				system("cls");
				
			}
				break;
			}
		}
			break;
		case 2 :
			howtoplayMenu();
			break;
		case 3 :
			exitGame = true;
			break;
		}
		exitGame = true;
	}
	return 0;
}