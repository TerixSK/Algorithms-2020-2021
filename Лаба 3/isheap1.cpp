#include <fstream>
#include <cstdlib>
using namespace std;
int main()
{
    ifstream fin("isheap.in");
    ofstream fout("isheap.out");
    int n;
    fin >> n;
    // Создание массива и основной цикл проверки обратного условия
    int arr[10000];
    fin >> arr[1];
    int k = 1;
    for (int i = 2; i <= n; ++i)
    {
        fin >> arr[i];
        if (i % 2 == 0)
        {
            if (arr[i / 2] > arr[i]) // Если обратное условие выполняется, прога прерывает работу
            {
                fout << "NO";
                break;
            }
        }
        else
        {
            if (arr[(i - 1) / 2] > arr[i])
            {
                fout << "NO";
                break;
            }
        }
        k += 1;
    }
    if (k == n) { fout << "YES"; }
    fin.close();
    fout.close();
    return 0;
}