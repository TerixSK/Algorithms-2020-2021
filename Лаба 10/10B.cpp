#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector < vector<int> > g; // граф
vector<bool> used; // вектор меток
vector<pair<int, int>> point; // вектор для хранения входящих данных
vector<double> dist; // вектор для хранения дистанции между точками

int distance(pair<int, int> a, pair<int, int> b) // функция для полсчёта дистанции между двумя точками
{
    int d;
    d = pow(b.first - a.first, 2)+ pow(b.second - a.second, 2);
    return d;
}

void prim(int start, int n)
{
    dist[start] = 0; // дистанция от первой точки до неё саой равно 0
    for (int i = 0; i < n; i++) // цикл по всем вершинам графа
    {
        int minID = -1; // миню вес
        // мы проходимся по всем смежным вершинам и ищем ребро с меньшим весом
        for (int j = 0; j < n; j++) // проход по смежным вершинам
            if (used[j] == false && (minID == -1 || dist[j] < dist[minID])) // если мы ещё не пометели вершину и если ребро имеет меньшей вес
                minID = j; // ребро с меньшим весом становиться минимальным
        used[minID] = true; // ставим метку на вершину, которую обошли
        for (int j = 0; j < n; j++) // проход по смежным вершинам
            if (used[j] == false && g[minID][j] < dist[j] && minID != j) // если мы ещё не пометели вершину и нахоим наш минимум
                dist[j] = g[minID][j]; // заполняем дистанцию
    }
}

int main()
{
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");
    int n;
    fin >> n;
    g.assign(n, vector<int>(n)); // подгон векторов по кол-во вершин
    used.resize(n, false);
    point.resize(n);
    dist.resize(n);
    for (int i = 0; i < n; i++) // считываем данные о точках
        fin >> point[i].first >> point[i].second;
    for (int i = 0; i < n; i++)
        dist[i] = numeric_limits<int>::max();
    for (int i = 0; i < n; i++) // зполняем граф по принципу
        for (int j = 0; j < n; j++) // в клетке i j храниться длинна от i до j
            g[i][j] = distance(point[i], point[j]);
    prim(0, n); // используем функцию
    double ans = 0; // вектор для ответа
    for (int i = 0; i < n; i++)
        ans += sqrt(dist[i]);
    fout << setprecision(10) << ans; // вывод числа с 10 знаками после заптой
    return 0;
}