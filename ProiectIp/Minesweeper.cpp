#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <climits>
using namespace std;
int grid[55][55], clicked[55][55], lines, columns, bombs;

void matrixGeneration(int grid[55][55], int height, int width, int bombs) {
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

void afisare(int grid[55][55],int clicked[55][55], int height, int width)
{	
	for (int i = -1; i <= height; i++) {
		for (int j = -1; j <= width; j++)
			if (i == -1 || j == -1 || i == height || j == width) {
				cout << char(grid[i][j]);
			}
			else
				if (clicked[i][j] == 2)
					cout << "?";
				else
					if (clicked[i][j] == 0)
						cout << "#";
					else
						if (clicked[i][j] == 1)
							if (grid[i][j] == -1)
								cout << char(233);
							else
								if (grid[i][j] == 0)
									cout << " ";
								else
									cout << grid[i][j];
		cout << endl;
	}
	cout << " CLICK HERE TO RETURN TO MENU " << endl;
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
		if (x > 0 && clicked[x - 1][y - 1] == 0 && y > 0)
			modify(x - 1, y - 1, height, width);
		if (x > 0 && clicked[x - 1][y + 1] == 0 && y<width)
			modify(x - 1, y + 1, height, width);
		if (x < height&&y>0 && clicked[x + 1][y - 1] == 0)
			modify(x + 1, y - 1, height, width);
		if (x < height && y < width && clicked[x + 1][y + 1] == 0)
			modify(x + 1, y + 1, height, width);
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
		if (x >= 16 && x <= 26 && y == 11)
			return 2;
		else
			if (x >= 16 && x <= 19 && y == 13)
				return 3;
	return 0;
}

void howtoplayMenu() {
	cout << char(201);
	for (int i = 0; i < 108; i++)
		cout << char(205);
	cout << char(187) << endl;
	cout << char(186) << "      QUICK START:                                                                                          " << char(186) << endl;
	cout << char(186) << " - You are presented with a board of squares.                                                               " << char(186) << endl;
	cout << char(186) << " - Some squares contain mines (bombs), others don't.                                                        " << char(186) << endl;
	cout << char(186) << " - If you click on a square containing a bomb, you lose.                                                    " << char(186) << endl;
	cout << char(186) << " - If you manage to click all the squares (without clicking on bombs) you win.                              " << char(186) << endl;
	cout << char(186) << " - Clicking a square which doesn't have a bomb reveals the number of neighbouring squares containing bombs. " << char(186) << endl;
	cout << char(186) << " - Use this information plus some guess work to avoid the bombs.                                            " << char(186) << endl;
	cout << char(186) << "      CONTROLS:                                                                                             " << char(186) << endl;
	cout << char(186) << " - To open a square, point at the square and click on it.                                                   " << char(186) << endl;
	cout << char(186) << " - To mark a square you think is a bomb, point and right-click.                                             " << char(186) << endl;
	cout << char(186) << "                                                                                                            " << char(186) << endl;
	cout << char(186) << " CLICK HERE TO RETURN TO MENU                                                                               " << char(186) << endl;
	cout << char(200);
	for (int i = 0; i < 108; i++)
		cout << char(205);
	cout << char(188) << endl;
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

void resetare(int a[55][55], int lines, int columns) {
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			a[i][j] = 0;
}

int verify(int height, int width) {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (clicked[i][j] == 0 && grid[i][j] != -1)
				return 0;
	return 1;
}

void firstClick(short x, short y, int lines, int columns) {
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
			clicked[i][j] = 1;
	if (grid[x][y] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x][y] = 0;
					grid[i][j] = -1;
					i = lines;
					j = columns;
				}
	if (grid[x - 1][y] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x - 1][y] = 0;
					grid[i][j] = -1;
					i = lines;
					j = columns;
				}
	if (grid[x - 1][y - 1] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x][y] = 0;
					grid[i][j] = -1;
					clicked[i][j] = 0;
					i = lines;
					j = columns;
				}
	if (grid[x - 1][y + 1] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x-1][y+1] = 0;
					grid[i][j] = -1;
					clicked[i][j] = 0;
					i = lines;
					j = columns;
				}
	if (grid[x][y - 1] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x][y-1] = 0;
					grid[i][j] = -1;
					clicked[i][j] = 0;
					i = lines;
					j = columns;
				}
	if (grid[x][y + 1] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x][y+1] = 0;
					grid[i][j] = -1;
					clicked[i][j] = 0;
					i = lines;
					j = columns;
				}
	if (grid[x + 1][y - 1] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x+1][y-1] = 0;
					grid[i][j] = -1;
					clicked[i][j] = 0;
					i = lines;
					j = columns;
				}
	if (grid[x + 1][y] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x+1][y] = 0;
					grid[i][j] = -1;
					clicked[i][j] = 0;
					i = lines;
					j = columns;
				}
	if (grid[x + 1][y + 1] == -1)
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				if (grid[i][j] != -1 && clicked[i][j] == 0) {
					grid[x+1][y+1] = 0;
					grid[i][j] = -1;
					clicked[i][j] = 0;
					i = lines;
					j = columns;
				}
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			if (grid[i][j] != -1)
				grid[i][j] = 0;
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
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
	resetare(clicked, lines, columns);
}

int gameStart(int height, int width) {
	short clickX, clickY;
	int clickType;
	bool firstChoice = false;
	while (!verify(height, width)) {
		system("cls");
		afisare(grid, clicked, height, width);
		click(clickY, clickX, clickType);
		clickX--;
		clickY--;
		while (clickX > height + 2 || clickY > 29)
			click(clickY, clickX, clickType);
		if (clickType == 2)
			if (clickX >= 0 && clickX < height&&clickY >= 0 && clickY < width && clicked[clickX][clickY]==0)
				if (clicked[clickX][clickY] == 2)
					clicked[clickX][clickY] = 0;
				else
					clicked[clickX][clickY] = 2;
			else;
		else {
			if (!firstChoice) {
				firstClick(clickX, clickY, height, width);
				firstChoice = true;
			}
			if (clickX >= 0 && clickX < height&&clickY >= 0 && clickY < width && clicked[clickX][clickY] != 2)
				if (grid[clickX][clickY] == -1 && clicked[clickX][clickY] == 0)
					return 0;
				else
					modify(clickX, clickY, height, width);
			else
				if (clickY + 1 > 0 && clickY + 1 <= 28 && clickX + 1 == height + 2 && clicked[clickX][clickY] != 2)
					return -1;
		}
	}
	return 1;
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
				click(mouseX, mouseY, mouseType);
				difSelect = dificultySelection(mouseX, mouseY);
			}
			switch (difSelect) {
			case 1: {
				system("cls");
				lines = 9;
				columns = 9;
				bombs = 10;
				resetare(grid, lines, columns);
				resetare(clicked, lines, columns);
				matrixGeneration(grid, lines, columns, bombs);
			}
					break;
			case 2: {
				system("cls");
				lines = 16;
				columns = 16;
				bombs = 40;
				resetare(grid, lines, columns);
				resetare(clicked, lines, columns);
				matrixGeneration(grid, lines, columns, bombs);
			}
					break;
			case 3: {
				system("cls");
				lines = 16;
				columns = 30;
				bombs = 99;
				resetare(grid, lines, columns);
				resetare(clicked, lines, columns);
				matrixGeneration(grid, lines, columns, bombs);
			}
					break;
			case 4: {
				system("cls");
				cout << "LINES(min 2; max 50):";
				cin >> lines;
				while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << endl << "You can only enter numbers!" << endl;
					cout << "LINES(min 2; max 50):";
					cin >> lines;
				}
				if (lines > 50)
					lines = 50;
				if (lines < 2)
					lines = 2;
				cout << endl << "COLUMNS(min 2; max 50):";
				cin >> columns;
				while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << endl << "You can only enter numbers!" << endl;
					cout << "COLUMNS(min 2; max 50):";
					cin >> columns;
				}
				if (columns > 50)
					columns = 50;
				if (columns < 2)
					columns = 2;
				cout << endl << "BOMBS(min 1; max " << (lines*columns) - 1 << "):";
				cin >> bombs;
				while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << endl << "You can only enter numbers!" << endl;
					cout << "BOMBS(min 1; max " << (lines*columns) - 1 << "):";
					cin >> bombs;
				}
				if (bombs > lines*columns - 1)
					bombs = lines*columns - 1;
				if (bombs < 1)
					bombs = 1;
				resetare(grid,lines,columns);
				resetare(clicked,lines,columns);
				matrixGeneration(grid, lines, columns, bombs);
			}
					break;
			}
			int gameResult = gameStart(lines, columns);
			system("cls");
			if (gameResult == 0) {
				cout << " YOU LOST " << endl;
				for (int i = 0; i < lines; i++)
					for (int j = 0; j < columns; j++)
						if (grid[i][j] == -1)
							clicked[i][j] = 1;
			}
			else
				if (gameResult == 1) {
					cout << " YOU WIN " << endl;
					for (int i = 0; i < lines; i++)
						for (int j = 0; j < columns; j++)
							if (grid[i][j] == -1)
								clicked[i][j] = 2;
				}
			if (gameResult != -1) {
				afisare(grid, clicked, lines, columns);
				click(mouseY, mouseX, mouseType);
				while (mouseType != 1 || mouseX != lines + 3 || mouseY < 1 || mouseY>29)
					click(mouseY, mouseX, mouseType);
			}
			system("cls");
		}
			break;
		case 2: {
			system("cls");
			howtoplayMenu();
			click(mouseX, mouseY, mouseType);
			while (mouseY != 12 || mouseX < 2 || mouseX>29 || mouseType == 2)
				click(mouseX, mouseY, mouseType);
			system("cls");
		}
			break;
		case 3: {
			system("cls");
			exitGame = true;
		}
			break;
		}
	}
	return 0;
}