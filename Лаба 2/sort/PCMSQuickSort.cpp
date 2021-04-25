#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

void quicksort(int* a, int n1) // n1 - ������ ������������ �������
{
	int i = 0; //left
	int j = n1 - 1; //right
	int mid = a[rand() % n1]; // ���������� �������� �������� ����� rand
	do
	{
		// ��������� �������� �� ��, ��� ������ � ������ ��������
		while (a[i] < mid)
		{
			i++;
		}
		while (a[j] > mid)
		{
			j--;
		}
		// Swap
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (j > 0)
	{
		quicksort(a, j + 1);
	}
	if (i < n1)
	{
		quicksort(&a[i], n1 - i);
	}
}
int main() {
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	int n;
	fin >> n;
	// �������� �������
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i];
	}
	// ������������� ������� 
	quicksort(arr, n);
	// ����� �������
	for (int i = 0; i < n; i++)
	{
		fout << arr[i] << " ";
	}
	delete[]arr;
	fin.close();
	fout.close();
	return 0;
}