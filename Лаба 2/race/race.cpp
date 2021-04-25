#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
// Строки через структуру
struct person
{
	string country, man;
	int where{};
};
// Функция быстрой сортировки для строк
void quicksort(person* a, int left, int right)
{
	int i, j, k;
	string m;
	k = a[(left + right) / 2].where;
	i = left;
	j = right;
	m = a[(left + right) / 2].country;
	while (i <= j)
	{
		while ((a[i].country < m) || ((a[i].country == m) && (a[i].where < k)))
		{
			i++;
		}
		while ((a[j].country > m) || ((a[j].country == m) && (a[j].where > k)))
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
	if (left < j)
	{
		quicksort(a, left, j);
	}
	if (i < right)
	{
		quicksort(a, i, right);
	}
}

int main()
{
	ifstream fin("race.in");
	ofstream fout("race.out");
	int n;
	fin >> n;
	// Ввод массива строк
	person* arr = new person[n];
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i].country >> arr[i].man;
		arr[i].where = i + 1;
	}
	// Исп. функции
	quicksort(arr, 0, n - 1);
	// Вывод массива строк
	for (int i = 0; i < n; i++)
	{
		if (arr[i].country != arr[i - 1].country)
		{
			fout << "=== " << arr[i].country << " ===" << endl;
		}
		fout << arr[i].man << endl;
	}
	fin.close();
	fout.close();
	return 0;
}
