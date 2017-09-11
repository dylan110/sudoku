#include<iostream>
#include<stdio.h>
#include<ctime>
#include<string>
#include<cstring>
#include<sstream>
#include <fstream>
#include <cstdlib>
using namespace std;


int num[9][9];
void Output();
bool Check(int n, int key);
bool DFS(int n);

int main(int argc, char* argv[])
{
	srand(time(0));
	int N;
	//scanf_s("%d", &N);
	N = atoi(argv[2]);//字符串转化为整数
	if (argc !=3) 
	{
		cout << "error!please enter two parameter " << endl;
		return 0;
	}
	if (strcmp(argv[1],"-c")!=0)
	{
		cout << "error!the first parameter must be \" -c \" " <<endl;
		return 0;
	}
	if (N == 0) cout << "error!please enter a integer greater than zero " << endl;//错误提醒
	for (int k = 1; k <= N; k++)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				num[i][j] = 0;
			}
		}
		num[0][0] = 2;
		if (DFS(1))
			Output();
	}
	return 0; 
}




/* 输出数独矩阵 */
void Output()
{
	ofstream file("sudoku.txt", ios::app);
	if (file.is_open())
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				file << num[i][j];
				if (j != 8) file << " ";
				//cout << num[i][j] << " ";
				if (j == 8) file << "\n";
			}
			if (i == 8)
			{
				file << "\n";
				//cout << endl;
			}
		}
	}
	file.close();

}



/* 判断value填入n时是否满足条件 */
bool Check(int n, int value)
{


	for (int i = 0; i < 9; i++)
	{
		/* j为n竖坐标 */
		int j = n / 9;
		if (num[j][i] == value) return false;
	}


	for (int i = 0; i < 9; i++)
	{
		/* j为n竖坐标 */
		int j = n % 9;
		if (num[i][j] == value) return false;
	}


	int x = n / 9 / 3 * 3;
	int y = n % 9 / 3 * 3;
	for (int i = x; i < x + 3; i++)
	{
		for (int j = y; j < y + 3; j++)
		{
			if (num[i][j] == value) return false;
		}
	}

	/* 全部合法，返回正确 */
	return true;

}

/* 深搜构造数独 */
bool DFS(int n)
{
	if (n > 80) {
		return true;
	}
	int j = 8;
	int k = 0;
	int b[9];
	num[n / 9][n % 9] = 0;
	for (int i = 1; i <= 9; i++)
	{
		if (Check(n, i) == true) b[k++] = i;

	}
	if (k == 0) {
		num[n / 9][n % 9] = 0;
		return false;
	}
	else
	{
		k++;
		do
		{
			k--;
			if (k == 0) {
				num[n / 9][n % 9] = 0;
				return false;
			}
			int pos = rand() % k;
			num[n / 9][n % 9] = b[pos];
			swap(b[pos], b[k - 1]);
		} while (!DFS(n + 1));
		return true;
	}
}
