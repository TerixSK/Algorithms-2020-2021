#include <fstream>
using namespace std;

int main()
{
    ifstream fin("isheap.in");
    ofstream fout("isheap.out");
    int n;
    fin >> n;
    // Создание массива
    int arr[100000];
    for (int i = 1; i <= n; i++)
    {
        fin >> arr[i];
    }
    // Основый цикл проверки условия
    int k = 0; // k - счётчик по проверки условия
    for (int i = 1; i <= n; i++)
    {
        if (i >= 1 && i <= n)
        {
            if (2 * i <= n)
            {
                if (arr[i] <= arr[2 * i])
                {
                    k += 1;
                }
            }
            if (2 * i + 1 <= n)
            {
                if (arr[i] <= arr[2 * i + 1])
                {
                    k += 1;
                }
            }
        }
    }
    // Вывод ответа
    if (k == n - 1) { fout << "YES"; }
    else { fout << "NO"; }
    fin.close();
    fout.close();
    return 0;
}