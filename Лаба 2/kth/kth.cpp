#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

// Функция быстрой сортировки
void quicksort(vector<int>& a, int left, int right, int k)
{
	int i, j, mid;
	i = left;
	j = right;
	mid = a[(right + left) / 2]; // Вычисление опорного элемента
	while (i <= j)
	{
		while (a[i] < mid)
		{
			i++;
		}
		while (a[j] > mid)
		{
			j--;
		}
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if ((left < j) && (k <= j)) // Сортировка для половинок массива
	{
		quicksort(a, left, j, k);
	}
	if ((i < right) && (k >= i))
	{
		quicksort(a, i, right, k);
	}
}

int main()
{
	ifstream fin("kth.in");
	ofstream fout("kth.out");
	int n, k, A, B, C;
	fin >> n >> k;
	// Создание массива
	vector<int> arr(n);
	fin >> A >> B >> C >> arr[0] >> arr[1];
	for (int i = 2; i < n; i++)
	{
		arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
	}
	// Использование функции
	quicksort(arr, 0, n - 1, k - 1);
	// Вывод ответа
	fout << arr[k - 1];
	fin.close();
	fout.close();
	return 0;
}
