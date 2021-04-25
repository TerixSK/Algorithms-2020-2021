#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

// Функция для преобразования в двоичную кучу поддерева с корневым узлом i
void heapify(int a[], int n, int i)
{
    int largest = i; // Наибольший элеменет = корень
    int l = 2 * i + 1; // l - лист
    int r = 2 * i + 2; // r - корень
     // Если левый дочерний элемент больше корня
    if (l < n && a[l] > a[largest])
        largest = l;
    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && a[r] > a[largest])
        largest = r;
    if (largest != i) // Проверка если наибольший элемент не корень
    {
        swap(a[i], a[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(a, n, largest);
    }
}

// Основная функция
void heapsort(int a[], int n)
{
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        swap(a[0], a[i]); // Перемещаем текущий корень в конец

        heapify(a, i, 0); // Вызываем процедуру heapify на уменьшенной куче
    }
}

int main()
{
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    int n;
    fin >> n;
    // Создание массива
    int arr[100000];
    for (int i = 0; i < n; i++) { fin >> arr[i]; }
    // Исп. фукции
    heapsort(arr, n);
    // Вывод массива
    for (int i = 0; i < n; i++) { fout << arr[i] << " "; }
    fin.close();
    fout.close();
    return 0;
}