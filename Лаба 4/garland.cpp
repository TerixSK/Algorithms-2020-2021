#include <fstream>
using namespace std;

/*
 * h[i]     = (h[i - 1] + h[i + 1]) / 2 - 1
 * 2 * h[i] = h[i - 1] + h[i + 1] - 2
 * h[i + 1] = 2 * h[i] - h[i - 1] + 2
 */

int garland(double* arr, int n, double y2)
{
	int f1 = 0; // f - переменная флаг
	arr[1] = y2;
	for (int i = 2; i < n; i++)
	{
		arr[i] = 2 * arr[i - 1] + 2 - arr[i - 2]; // задаём оставшиеся эл. массива по формуле
		if (arr[i] <= 0.0001 && arr[i] >= -0.0001)
			f1 = 1;
		if (arr[i] < -0.0001)
			return 2;
	}
	if (f1 == 0)
		return 0;
	if (f1 == 1)
		return 1;
}

// Используем бинарный поиск
double binsearch(double* arr, int n1, double min, double max)
{
	double mid = (max + min) / 2; // средний элемент
	int f2 = garland(arr, n1, mid); // f - переменная флаг
	if (f2 == 0)
		return binsearch(arr, n1, min, mid);
	else if (f2 == 1)
		return mid;
	else if (f2 == 2)
		return binsearch(arr, n1, mid, max);
}

int main()
{
	ifstream fin("garland.in");
	FILE* fout = fopen("garland.out", "w");

	int n;
	fin >> n;
	double A;
	fin >> A;
	double* arr = new double[n];
	arr[0] = A;
	double y2 = binsearch(arr, n, 0, A);
	double B = (n - 1) * (y2 + n - 2) - A * (n - 2);
	fprintf(fout, "%.2lf", B);
	return 0;
}