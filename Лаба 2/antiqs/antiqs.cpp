#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ifstream fin("antiqs.in");
    ofstream fout("antiqs.out");
    long n;
    fin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
    for (int i = 2; i < n; i++)
    {
        int temp = a[i];
        a[i] = a[i / 2];
        a[i / 2] = temp;
    }
    for (int i = 0; i < n; i++)
    {
        fout << a[i] << ' ';
    }
    fin.close();
    fout.close();
    return 0;
}