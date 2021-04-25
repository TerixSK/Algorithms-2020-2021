#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	int n;
	ifstream fin("smallsort.in");
	ofstream fout("smallsort.out");
	fin >> n;
	// Создание массива
	long long sort[10000];
	for (int i = 0; i < n; i++)
	{
		fin >> sort[i];
	}
	// Сортировка вставками
	for (int i = 1; i < n; i++)
	{
		for (int j = i; j > 0 && sort[j - 1] > sort[j]; j--)
		{
			swap(sort[j - 1], sort[j]);
		}
	}
	// Вывод массива
	for (int i = 0; i < n; i++)
	{
		fout << sort[i] << " ";
	}
	fin.close();
	fout.close();
	return 0;
}