#include <iostream>
#include <cstdlib>
using namespace std;
int a[50][50];
void matrixGeneration(int a[50][50], int height, int width, int bombs) {
	int bomsOnMap = 0;
	a[-1][-1] = 201;
	a[-1][width] = 187;
	a[height][-1] = 200;
	a[height][width] = 188;
	for (int i = 0; i < width; i++){
		a[-1][i] = 205;
		a[height][i] = 205;
	}
	for (int i = 0; i < height; i++) {
		a[i][-1] = 186;
		a[i][width] = 186;
	}
	while (bomsOnMap < bombs) {
		int x, y;
		x = rand() % height;
		y = rand() % width;
		if (a[x][y] != -1) {
			a[x][y] = -1;
			bomsOnMap++;
		}
	}
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (a[i][j] != -1) {
				if (a[i - 1][j] == -1)
					a[i][j]++;
				if (a[i - 1][j - 1] == -1)
					a[i][j]++;
				if (a[i - 1][j + 1] == -1)
					a[i][j]++;
				if (a[i][j - 1] == -1)
					a[i][j]++;
				if (a[i][j + 1] == -1)
					a[i][j]++;
				if (a[i + 1][j - 1] == -1)
					a[i][j]++;
				if (a[i + 1][j] == -1)
					a[i][j]++;
				if (a[i + 1][j + 1] == -1)
					a[i][j]++;
			}
}

void afisare(int a[50][50], int height, int width)
{	
	for (int i = -1; i <= height; i++) {
		for (int j = -1; j <= width; j++)
			if (i == -1 || j == -1 || i == height || j == width) {
				cout << char(a[i][j]);
				if (i == -1 && a[i][j] != 187 && a[i][j] != 201 && j != width - 1)
					cout << char(209);
				else
					if (i == height && a[i][j] != 200 && a[i][j] != 188 && j != width - 1)
						cout << char(207);
			}
			else
				if (a[i][j] == -1)
					if (j == height - 1)
						cout << char(178);
					else
						cout << char(178) << char(179);
				else
					if (j == height - 1)
						cout << a[i][j];
					else
						cout << a[i][j] << char(179);
		cout << endl;
		if (i != -1 && i != height - 1 && i != height) {
			cout << char(199);
			for (int k = 0; k < width-1; k++)
				cout << char(196) << char(197);
			cout <<char(196)<< char(182) << endl;
		}
	}
}

int main() {
	int x, y, b;
	cin>>x>>y>>b;
	matrixGeneration(a, x, y, b);
	afisare(a, x, y);
	return 0;
}