#include <fstream>
using namespace std;

string a[1000], arr[1000];

// Поразрядная сортировка для одной фазы
void radixsort(int ii, int n1)
{
    char z = 'a'; // Вспомогательный элемент
    int k = 0;
    for (int i = 0; i <= 26; i++) // i <= 26 потому что в англ. алфавите 26 букв 
    {
        for (int j = 0; j < n1; j++)
        {
            if (a[j][ii] == z)  // Сортировка по сиволам
            {
                arr[k] = a[j];
                k++;
            }
        }
        z++; // a меняется на b, b на c и так далее
    }
    for (int i = 0; i < n1; i++) { a[i] = arr[i]; }
}

int main()
{
    ifstream fin("radixsort.in");
    ofstream fout("radixsort.out");
    long n, m, k; // n - кол-во строк m - их длинна k - число фаз сортировки 
    fin >> n >> m >> k;
    // Создание массива
    for (int i = 0; i < n; i++) { fin >> a[i]; }
    // Использование функции взависимоти от числа фаз
    for (int i = m - 1; i >= m - k; i--) { radixsort(i, n); }
    // Вывод итоговой последовательности
    for (int i = 0; i < n; i++) { fout << a[i] << '\n'; }
    return 0;
}