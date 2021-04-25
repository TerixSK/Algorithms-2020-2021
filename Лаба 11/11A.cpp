#include<fstream>
#include<vector>

using namespace std;

const long long infinity = 1000000000000000; // бесконечность
vector<vector<long long>> g; // граф
vector<bool> used; // вектор меток
vector<long long> dist; // вектор, котрый хранит дистанцию от стартовой точки до других

void Dijkstra(long long start, int n) // Алгоритм Дейкстра
{
    dist[start] = 0;
    for (long long i = 0; i < n; i++) // делаем проход по всем вершинам
    {
        long long v = -1;
        for (long long j = 0; j < n; j++) // делаем проход по всем путям из точки
            if (used[j] == false && (v == -1 || dist[j] < dist[v])) // выбираем вершину с наим. dist[v] среди не помеченных
                v = j; // заполянем путь
        if (dist[v] == infinity) // если до вершины нельзя добраться
            break; // то выходим из цикла
        used[v] = true; // помечаем вершину
        for (long long j = 0; j < n; j++) // улучшаем результат
            if (dist[v] + g[v][j] < dist[j])
                dist[j] = dist[v] + g[v][j];
    }
}

int main()
{
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");
    int n, start, finish, v;
    fin >> n >> start >> finish;
    g.resize(n, vector<long long> (n));
    used.resize(n, false);
    dist.resize(n, infinity);
    for (int i = 0; i < n; i++) // считываем входные данные
        for (int j = 0; j < n; j++)
        {
            fin >> v;
            v < 0 ? g[i][j] = infinity : g[i][j] = v; // заполянем только, иходящие пути
        }
    Dijkstra(start - 1, n);
    dist[finish - 1] != infinity ? fout << dist[finish - 1] : fout << "-1";
    return 0;
}