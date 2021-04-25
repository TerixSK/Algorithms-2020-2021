#include <fstream>
#include <vector>
#define ll long long
using namespace std;

vector<vector<pair<ll, ll>> > g; // граф
const ll infinity = LONG_LONG_MAX; // бесконечность

vector<ll> BellmanFord(ll start, ll n) // Алгоритм Беллмона Форда
{
    vector<ll> dist(n, infinity);
    dist[start] = 0;
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < n; j++)
            for (ll k = 0; k < g[j].size(); k++)
                if ((dist[j] < infinity) && (dist[g[j][k].second] > dist[j] + g[j][k].first))
                    dist[g[j][k].second] = dist[j] + g[j][k].first;
    return  dist;
}

void dfs(ll v, vector<int>& used) // Обход графа в глубуину
{
    used[v] = 1;
    for (auto & i : g[v])
        if (used[i.second] == false)
            dfs(i.second, used);
}

int main() {
    ifstream fin("path.in");
    ofstream fout("path.out");
    ll n, m, start, v1, v2, w;
    fin >> n >> m >> start;
    start--;
    g.resize(n);
    for (int i = 0; i < m; i++)
    {
        fin >> v1 >> v2 >> w;
        v1--, v2--;
        g[v1].push_back({w, v2}); // храним пару вес и точку с которой соеден
    }
    vector<ll> d = BellmanFord(start, n); // считаем кратчайшее расстояние от стартовой до всех остальных вершин
    vector<int> used(n, false);
    for (int i = 0; i < n; i++) // проход по всем вершинам
        for (int j = 0; j < g[i].size(); j++) // проход по всем смежным вершинам
            if ((d[i] < infinity) && (d[g[i][j].second] > d[i] + g[i][j].first) && !used[g[i][j].second]) // если до вершины можно добраться и можно улучшить растю до неё
                dfs(g[i][j].second, used); // совершаем обход графа в глубину и расставляем метки
    for (int i = 0; i < n; i++) // выводим результат
        if (d[i] == infinity) // если расстояние так и осталось равна бесконечности
            fout << "*" << endl; // то до вершины нельзя добраться
        else if (used[i] || d[i] < -5e18) // если вершина помечена
            fout << "-" << endl; // то кратчайшего расстояния до этой вершины нет
        else
            fout << d[i] << endl; // иначе выводим расстояние
    return 0;
}