#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class priorityqueue
{
private:

    vector<int> a;
    int n = 0;

    void siftUp(int i) // Построение двоичного дерева Min, для добовления в очередь
    {
        if ((i > 0) && (a[i] < a[(i - 1) / 2]))
        {
            swap(a[i], a[(i - 1) / 2]);
            siftUp((i - 1) / 2);
        }
    }

    void siftDown(int i) // Построение двоичного дерева Max
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;
        if ((l < n) && (a[i] > a[l]))
            largest = l;
        if ((r < n) && (a[largest] > a[r]))
            largest = r;
        if (largest != i)
        {
            swap(a[i], a[largest]);
            siftDown(largest);
        }
    }

    int findKey(int mas)  // Поиск
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i] == mas)
                return i;
        }
        return -1;
    }

public:
    priorityqueue()
    {
        a.resize(1000000);
    }

    void push(int mas) // Добавить элемент в очередь
    {
        a[n] = mas;
        siftUp(n++);
    }

    int extractMin() // Удалить мин. эл. и вевести в выходный файл (или *, если очередь пуста)
    {
        if (n > 0)
        {
            int value = a[0];
            a[0] = a[--n];
            siftDown(0);
            return value;
        }
        else
            return -1000000001;
    }

    void decreaseKey(int mas, int newNumber) // Замена эл., добавленного push ом, на другой в выходной файл (x -> y)
    {
        int index = findKey(mas); // мы используем функцию поиска
        a[index] = newNumber; //  находим нужный элемент
        siftUp(index); // и делаем просеивание по мин элементу в корне
    }

};

int main()
{
    setlocale(LC_ALL, "Ru");
    ifstream fin("priorityqueue.in");
    ofstream fout("priorityqueue.out");
    priorityqueue priorit;
    vector<int> arr(1000000);
    string command;
    int x, y;
    int k = 0; // Счётчик
    // Чтение команд из файла
    while (!fin.eof())
    {
        command = "";
        fin >> command;
        if (command == "push")
        {
            fin >> x;
            priorit.push(x);
            arr[k] = x;
        }
        else if (command == "extract-min")
        {
            int min = priorit.extractMin();
            if (min > -1000000001)
                fout << min << endl;
            else
                fout << '*' << endl;
        }
        else if (command == "decrease-key")
        {
            fin >> x >> y;
            priorit.decreaseKey(arr[x - 1], y);
            arr[x - 1] = y;
        }
        k++;
    }
    fin.close();
    fout.close();
    return 0;
}