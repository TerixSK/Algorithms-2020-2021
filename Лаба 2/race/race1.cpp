#include <iostream>
#include <fstream>
using namespace std;

struct person
{
    string country;
    string man;
    int where;
};

person a[100000], arr[100000];
void mergeSort(long left, long right) {
    if (left < right) {
        long mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        long i = 0, j = 0;
        while (left + i <= mid && mid + 1 + j <= right)
        {
            if (a[left + i].country > a[mid + 1 + j].country)
            {
                arr[i + j] = a[mid + 1 + j];
                j++;
            }
            else
            {
                arr[i + j] = a[left + i];
                i++;
            }
        }
        while (left + i <= mid)
        {
            arr[i + j] = a[left + i];
            i++;
        }
        while (mid + 1 + j <= right)
        {
            arr[i + j] = a[mid + 1 + j];
            j++;
        }
        for (i = 0; i < right - left + 1; i++)
        {
            a[left + i] = arr[i];
        }
    }
}

int main()
{
    ifstream fin("race.in");
    ofstream fout("race.out");
    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> a[i].country >> a[i].man;
        a[i].where = i;
    }
    mergeSort(0, n - 1);
    string last;
    for (int i = 0; i < n; i++)
    {
        if (last != a[i].country)
        {
            fout << "=== " << a[i].country << " ===" << endl;
            last = a[i].country;
        }
        fout << a[i].man << endl;
    }
    fin.close();
    fout.close();
    return 0;
}