#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;
void Merge(int* A, int left, int right)
{
	int mid, l, r;
	int* mas = new int[100];
	mid = (left + right) / 2; //вычисление опорного элемента
	l = left; //начало левой части
	r = mid + 1; //начало правой части
	for (int i = left; i <= right; i++)
		if ((l <= mid) && ((r > right) || (A[l] < A[r])))
		{
			mas[i] = A[l];
			l++;
		}
		else
		{
			mas[i] = A[r];
			r++;
		}
	for (int i = left; i <= right; i++)
	{
		A[i] = mas[i];
	}
	delete[]mas;
}
//Рекурсия
void MergeSort(int* A, int left, int right)
{
	int l = left, r = right;
	{
		if (l < r)
		{
			MergeSort(A, l, (l + r) / 2); //сортировка левой части
			MergeSort(A, (l + r) / 2 + 1, r); //сортировка правой части
			Merge(A, l, r); //слияние двух частей
		}
	}
}
int main()
{
	ifstream fin("inversions.in");
	ofstream fout("inversions.out");
	int n;
	int kol_vo = 0;
	fin >> n;
	// Создание массива
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i];
	}
	// Сортировка
	MergeSort(arr, 0, n - 1);
	// Вывод
	for (int i = 0; i < n; i++)
	{
		fout << arr[i] << " ";
	}
	delete[]arr;
	fin.close();
	fout.close();
	return 0;
}