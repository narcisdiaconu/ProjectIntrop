#include <iostream>
#include <cstdlib>
using namespace std;
void matrixGeneration(int a[50][50], int height, int width, int bombs) {
	int bomsOnMap = 0;
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
int a[50][50];
int main() {
	int x, y, b;
	cin>>x>>y>>b;
	matrixGeneration(a, x, y, b);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	return 0;
}