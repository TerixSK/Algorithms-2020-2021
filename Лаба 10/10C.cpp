#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge // структура для ребра, которая хранит
{
    int v1, v2; // вершины, из которых состоит
    int weight; // и вес ребра
    bool operator < (Edge e) const // Также два метода для сравнения рёбер
    {
        return this->weight < e.weight;
    }
    bool operator > (Edge e) const
    {
        return this->weight > e.weight;
    }
};

vector<Edge> g;
vector<int> parent;

int get_root(int v)
{
    if (parent[v] == v)
        return v;
    else
    {
        int root;
        root = get_root(parent[v]);
        parent[v] = root;
        return root;
    }
}

int main()
{
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");
    int n, m, v1, v2, w;
    fin >> n >> m;
    g.resize(m);
    parent.resize(n);
    for (int i = 0; i < m; i++)
    {
        fin >> v1 >> v2 >> w;
        v1--;
        v2--;
        g[i].v1 = v1;
        g[i].v2 = v2;
        g[i].weight = w;
    }
    long long min_weight_tree = 0;
    sort(g.begin(), g.end()); // сортировка ребёр по весу
    for (int i = 0; i < n; i++)
        parent[i] = i;
    for (int i = 0; i < m; i++) // перебераем рёбра от первого до последнего
    {
        v1 = g[i].v1, v2 = g[i].v2, w = g[i].weight;
        if (get_root(v1) != get_root(v2)) // если у текущего ребра концы принадлежат разным поддеревьям
        { // обьеденяем поддеревья и
            min_weight_tree += w; // добовляем вес в ответ
            v1 = get_root(v1);
            v2 = get_root(v2);
            if (rand() & 1)
                swap (v1, v2);
            if (v1 != v2)
                parent[v1] = v2;
        }
    }
    fout << min_weight_tree;
    return 0;
}