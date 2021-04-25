#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge // структура для хранения информации о рёбрах
{
    int v1, v2; // концы ребра
    int weight; // вес ребра
};

bool check(const vector<vector<int>>& g, int root) // проверка графа на связность
{ // поскольку если хотя быодна вершина графа недостижима, то требуемое дерево невозможно построить
    queue<int> q;
    vector<int> used(g.size(), 0);
    used[root] = 1;
    q.push(root);
    while (!q.empty()) // делаем обход графа, помечая вершины
    {
        int b = q.front();
        for (int i : g[b])
            if (used[i] == 0)
            {
                used[i] = 1;
                q.push(i);
            }
        q.pop();
    }
    for (int i : used) // если после прохода хотя бы одна вершина осталось не помеченной
        if (i == 0)
            return false; // то граф не прошёл проверку
    return true; // иначе нужное дерево возможно построить
}

vector<int> order; // хранит результат топологической сортировки обычного графа
vector<int> component; // хранит результат топологической сотрировки транспонированного графа

void dfs1(vector<vector<int>>& g, vector<int>& used, int v) // топологическая сортировка для обычного графа
{
    used[v] = 1;
    for (int i: g[v])
        if (used[i] == 0)
            dfs1(g, used, i);
    order.push_back(v);
}

void dfs2(vector<vector<int>>& g, vector<int>& used, int v, int comp) // топологическая сортировка для транспонированного графа
{
    component[v] = comp;
    used[v] = 1;
    for (int i: g[v])
        if (used[i] == 0)
            dfs2(g, used, i, comp);
}


int condensation(int n, vector<Edge>& edge) // поиск кол-ва компонент сильной связности
{
    vector<vector<int>> G(n); // граф
    vector<vector<int>> GT(n); // транспонированный граф
    for (auto i : edge) // зан=полняем инфу
    {
        G[i.v1].push_back(i.v2);
        GT[i.v2].push_back(i.v1);
    }
    vector<int> used = vector<int>(n); // вектор меток
    component.resize(n);
    used.assign(n, 0);
    component.assign(n, -1);
    for (int i = 0; i < n; i++) // выполняем топологическую сортировку для обычного графа
        if (used[i] == 0)
            dfs1(G, used, i);
    used.assign(n, 0);
    int comp = 0;
    for (int i = 0; i < order.size(); i++) // выполняем топологическую сортировку для транспонированного графа
        if (component[order[order.size() - i - 1]] == -1)
            dfs2(GT, used, order[order.size() - i - 1], comp++);
    return comp; // выводим кол-во компонент сильной связности
}

long long mst(int n, const vector<Edge>& edge, int root, const vector<vector<int>>& g)
{
    long long ans = 0;
    vector<int> min_edge(n, INT_MAX); // создаем массив минимумов, входящих в каждую компоненту, инициализируем бесконечностью
    for (auto i : edge)
        min_edge[i.v2] = i.weight < min_edge[i.v2] ? i.weight : min_edge[i.v2];
    for (int i = 0; i < n; i++)
        if (i != root)
            ans += min_edge[i]; //веса минимальных ребер точно будут в результате
    vector<Edge> zero_edge; //создаем массив нулевых ребер
    vector<vector<int>> zero_g(n);
    for (auto i: edge)
        if (i.weight == min_edge[i.v2])
        {
            zero_edge.push_back({i.v1, i.v2, 0});
            zero_g[i.v1].push_back(i.v2);
        }
    if (check(zero_g, root)) // проверяем, можно ли дойти до всех вершин по нулевым ребрам
        return ans;
    int compc = condensation(n, zero_edge);
    vector<int> comp = component; // будущие компоненты связности
    vector<Edge> new_edge; //создаем массив ребер в новом графе с вершинами в полученных компонентах
    vector<vector<int>> new_g(compc);
    for (auto i : edge)
        if (comp[i.v1] != comp[i.v2]) // в разных компонентах добавляем в new_edge ребро с концами в данных компонентах и весом e.weight
        {
            new_edge.push_back({comp[i.v1], comp[i.v2], i.weight - min_edge[i.v2]});
            new_g[comp[i.v1]].push_back(comp[i.v2]);
        }
    ans += mst(compc, new_edge, comp[root], new_g);
    return ans;
}

int main()
{
    ifstream fin("chinese.in");
    ofstream fout("chinese.out");
    int n, m, v1, v2, w;
    fin >> n >> m;
    vector<Edge> edge(m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) // считываем данные
    {
        fin >> v1 >> v2 >> w;
        v1--;
        v2--;
        g[v1].push_back(v2);
        edge[i] = {v1, v2, w};
    }
    if (check(g, 0) == false) // выполняем проверку
    {
        fout << "NO";
        return 0;
    }
    fout << "YES" << endl << mst(n, edge, 0, g); // если граф прошёл проверку, то остаётся найти вес минимального остовного дерева
    return 0;
}