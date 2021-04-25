#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

//������� ����������
int partition(int* A, int p, int r)
{
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (A[j] <= x)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	return i + 1;
}
// ������� ��� ������������ �������� ��������
int randomized_partition(int* A, int p, int r)
{
	int i = rand() % r + p;
	swap(A[r], A[i]);
	return partition(A, p, r);
}
// ������� ������� ����������
void quicksort(int* A, int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

// �������� �������
int main()
{
	int n;
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	fin >> n;
	// �������� �������
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i];
	}
	// ������������� ������� 
	quicksort(arr, 0, n - 1);
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