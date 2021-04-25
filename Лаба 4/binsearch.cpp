#include <fstream>
using namespace std;

// Создание двух функций бин. поиска
// (Это его модифакция, которая ищет не само значение, а номера первого и последнего вхождения числа в массив)
int bin_search_0(int* arr, int key, int n1)
{
	int min = -1;
	int max = n1;
	while (min < max - 1) // пока конец - 1 > начала
	{
		int mid = (min + max) / 2; // вычисление среднего элемента
		if (arr[mid] < key) // если key > среднего, то рассматриваем вторую(которая > mid) половину массива 
			min = mid;
		else
			max = mid; // иначе, превую(которая < mid) половину массива
	}
	return max; // в итоге искомое значение становиться равным max, возвращаем его
}

int bin_search_n(int* arr, int key, int n1)
{
	int min = -1;
	int max = n1;
	while (min < max - 1)
	{
		int mid = (min + max) / 2;
		if (arr[mid] <= key) // знак <= обеспечивает нам нахождение последнего искомого числа
			min = mid;
		else
			max = mid;
	}
	return max - 1;
}

int main()
{
	ifstream fin("binsearch.in");
	ofstream fout("binsearch.out");
	int n;
	fin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		fin >> arr[i];
	int m;
	fin >> m;
	for (int i = 0; i < m; i++)
	{
		int key;
		fin >> key;
		if (bin_search_0(arr, key, n) > bin_search_n(arr, key, n))
			fout << "-1 -1\n";
		else
			fout << bin_search_0(arr, key, n) + 1 << " " << bin_search_n(arr, key, n) + 1 << endl;
	}
	return 0;
}

