#include <fstream>
using namespace std;

// �������� ���� ������� ���. ������
// (��� ��� ����������, ������� ���� �� ���� ��������, � ������ ������� � ���������� ��������� ����� � ������)
int bin_search_0(int* arr, int key, int n1)
{
	int min = -1;
	int max = n1;
	while (min < max - 1) // ���� ����� - 1 > ������
	{
		int mid = (min + max) / 2; // ���������� �������� ��������
		if (arr[mid] < key) // ���� key > ��������, �� ������������� ������(������� > mid) �������� ������� 
			min = mid;
		else
			max = mid; // �����, ������(������� < mid) �������� �������
	}
	return max; // � ����� ������� �������� ����������� ������ max, ���������� ���
}

int bin_search_n(int* arr, int key, int n1)
{
	int min = -1;
	int max = n1;
	while (min < max - 1)
	{
		int mid = (min + max) / 2;
		if (arr[mid] <= key) // ���� <= ������������ ��� ���������� ���������� �������� �����
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

