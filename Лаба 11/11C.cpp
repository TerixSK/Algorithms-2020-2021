#include <fstream>
#include <vector>
#include <set>
using namespace std;

vector<vector<pair<long long, long long>>> g;

vector<long long> Dijkstra(long long n) // Алгоритм Дейкстры
{
    vector<long long> dist(n, LONG_MAX);
    dist[0] = 0;
    set <pair<long long, long long>> queue; // используем set для хранения аершин по отсортированному расстоянию между вершинами
    queue.insert ({0, 0});
    while (!queue.empty()) {
        pair<long long, long long> v = *queue.begin(); // извлечение вершины
        queue.erase(queue.begin());
        for (auto& i : g[v.second]) //  релаксакция
        {
            if (dist[v.second] + i.first < dist[i.second])
            {
                queue.erase({dist[i.second], i.second});
                dist[i.second] = dist[v.second] + i.first;
                queue.emplace(pair<long long, long long>{dist[i.second], i.second});
            }
        }
    }
    return dist;
}

int main()
{
    ifstream fin ("pathbgep.in");
    ofstream fout ("pathbgep.out");
    long long n, m, x, y, len;
    fin >> n >> m;
    g.resize(n);
    for (long long j = 0; j < m; j++) // считываем данные
    {
        fin >> x >> y >> len;
        x--, y--;
        g[x].push_back({len, y});
        g[y].push_back({len, x});
    }
    vector<long long> d = Dijkstra(n);
    for (auto i : d)
        fout << i << ' ';
    return 0;
}