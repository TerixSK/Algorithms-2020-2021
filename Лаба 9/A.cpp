#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> g;
vector<bool> used;
vector<int> ans;

void topSort(int v) // топологическая сортировка
{ // обычный dfs только мы заржаем вершины в вектор
    used[v] = true;
    for (int i: g[v])
        if (!used[i])
            topSort(i);
    ans.push_back(v);
}

vector<string> color;
vector<int> cycle;
bool check(int v, int start, int finish) // проверка на циклы
{
    color[v] = "grey"; // помечаем вершину серой
    int temp;
    for (auto i: g[v]) // проходимся по всем связным вершинам
    {
        temp = i;
        if (color[temp] == "white") // если пришли в белую верщину
        {
            cycle[temp] = v;
            if (check(temp, start, finish)) // проверяем текущию вершину
                return true;
        }
        else if (color[temp] == "grey") // если пришли в серую вершину
        {
            start = temp;
            finish = v;
            return true;
        }
    }
    color[v] = "black"; // после прохода по вершине меняем цвет на чёрный
    return false;
}

int main()
{
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");
    int n, m, v1, v2, start = -1, finish = -1;
    fin >> n >> m;
    g.resize(n); // заполняем вектора изначальными значениями
    used.assign(n, false);
    color.assign(n, "white");
    cycle.assign(n, -1);
    for (int i = 0; i < m; i++) // считываем данные о вершинах
    { // и строим список смежности
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }
    for (int i = 0; i < n; i++) // осуществляем проверку
    {
        if (check(i, start, finish)) // если какая то вершина не прошла проверку
        { // то граф является цикличным
            fout << -1;
            return 0;
        }
    }
    for (int i = 0; i < n; i++) // запускаем для каждой точки топологическую сортировку
        if (!used[i])
            topSort(i);
    vector<int> ansReverse(n); // инвертируем вектор
    for (int i = 0; i < n; i++)
        ansReverse[i] = ans[n - 1 - i];
    for (auto i : ansReverse) // выводим результат
        fout << i + 1 << " ";
    return 0;
}