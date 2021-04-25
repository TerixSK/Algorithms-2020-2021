#include <fstream>
#include <vector>

using namespace std;

long long inv;

void mergesort_inv2(vector<int>& a, int left, int mid, int right)
{
	vector<int> mas;
	int l = left, r = right;
	mas.resize(r - l);
	int i, j;
	i = 0;
	j = 0;
	while (((l + i) < mid) && ((mid + j) < r))
	{
		if (a[l + i] <= a[mid + j])
		{
			mas[i + j] = a[l + i];
			i++;
		}
		else
		{
			mas[i + j] = a[mid + j];
			inv += mid - (l + i);
			j++;
		}
	}
	while ((l + i) < mid)
	{
		mas[i + j] = a[l + i];
		i++;
	}
	while ((mid + j) < r)
	{
		mas[i + j] = a[mid + j];
		j++;
	}
	for (int ii = 0; ii < (i + j); ii++)
	{
		a[l + ii] = mas[ii];
	}
}

void mergesort_inv1(vector<int>& a, int left, int right)
{
	int l = left, r = right;
	if ((l + 1) >= r)
	{
		return;
	}
	int mid;
	mid = (l + r) / 2;
	mergesort_inv1(a, l, mid);
	mergesort_inv1(a, mid, r);
	mergesort_inv2(a, l, mid, r);
}

int main()
{
	ifstream fin("inversions.in");
	ofstream fout("inversions.out");
	int n;
	fin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i];
	}
	mergesort_inv1(arr, 0, n);
	fout << inv;
	fin.close();
	fout.close();
	return 0;
}
