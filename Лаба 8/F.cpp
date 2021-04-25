#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

struct Dot // структура для хранения информации о точке
{
    int x;
    int y;
    string way; // хранит путь от старта до текущей точки
    bool passage; // можно или нельзя пройти в эту точку
};

void maze(Dot **arr, Dot start) // Функция, подсчёта кротчайшего расстояния до точки выхода из лабиринта
{
    queue<Dot> queue; // создаём очередь для хранения точек из которых можем куда нибудь пойти
    queue.push(start); // заряжаем стартовую точку
    while (!queue.empty()) // пока очередь не пуста
    {
        Dot p = queue.front(); // берём первый элемент из очереди
        queue.pop();
        if (arr[p.x + 1][p.y].passage && arr[p.x + 1][p.y].way == "") // если в точку можно пройти и в ней мы ещё не были
                                                                                                // то помещаем её в очередь
        {
            arr[p.x + 1][p.y].way = p.way + "D";
            queue.push(arr[p.x + 1][p.y]);
        }
        if (arr[p.x - 1][p.y].passage && arr[p.x - 1][p.y].way == "")
        {
            arr[p.x - 1][p.y].way = p.way + "U";
            queue.push(arr[p.x - 1][p.y]);
        }
        if (arr[p.x][p.y + 1].passage && arr[p.x][p.y + 1].way == "")
        {
            arr[p.x][p.y + 1].way = p.way + "R";
            queue.push(arr[p.x][p.y + 1]);
        }
        if (arr[p.x][p.y - 1].passage && arr[p.x][p.y - 1].way == "")
        {
            arr[p.x][p.y - 1].way = p.way + "L";
            queue.push(arr[p.x][p.y - 1]);
        }
    }
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;
    Dot **arr = new Dot*[n + 2]; // создаём двумерный рассширенный массив для хронения исходных данных и границ
    for (int i = 0; i < n + 2; i++)
    {
        arr[i] = new Dot[m + 2];
    }
    Dot start, finish; // создаём точку для начала и конца лабиринта
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < m + 2; j++)
        {
            arr[i][j].x = i; // заполняем координаты точек индексами матрицы
            arr[i][j].y = j;
        }
    }

    for (int i = 1; i < n + 1; i++) // считываем данные из файла и заполняем матрицу
    {
        for (int j = 1; j < m + 1; j++)
        {
            char dot;
            fin >> dot;
            if (dot == '#') // решётку помечаем, как непроходимаю клетку
                arr[i][j].passage = false;
            else
                arr[i][j].passage = true;
            if (dot == 'S') // для стартовой точки заполняем поля точки старта
            {
                start.x = i;
                start.y = j;
            }
            else if (dot == 'T') // для конечной точки заполняем поля точки старта
            {
                finish.x = i;
                finish.y = j;
            }
            arr[i][j].way = ""; // для каждой точке заполняем путь
        }
    }

    for (int i = 0; i < n + 2; i++) // заполняем вертикальные граница
    {
        arr[i][0].passage = false;
        arr[i][m + 1].passage = false;
    }
    for (int i = 0; i < m + 2; i++) // заполняем гооризонтальные граница
    {
        arr[0][i].passage = false;
        arr[n + 1][i].passage = false;
    }

    maze(arr, start); // исп. функцию

    if (arr[finish.x][finish.y].way == "") // если у конечной точки пустой путь
        fout << "-1" << endl; // то до неё нельзя добраться
    else
        fout << arr[finish.x][finish.y].way.length() << endl << arr[finish.x][finish.y].way; // иначе выводим путь для конечной точки
    return 0;
}
