#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> g;
vector<int> color;
bool flag = true;

void bfs(int v) // проверка на двудольность
{ // это bfs, в котрором мы будем делить граф на две доли
    // метки: 0 - не определена, 1 - первая доля, -1 - вторая доля.
    queue<int> q;
    color[v] = 1; // помещаем первую вершину в первую долю
    q.push(v);
    while(!q.empty()) // пока очередь не пуста
    {
        int temp = q.front();
        q.pop();
        for (auto i: g[temp]) // проходимся по всем связным вершинам
        {
            if (color[i] == 0) // если чвет не определён
            {
                q.push(i);
                color[i] = -color[temp]; // ставим противопожный относительно данной вершины
            }
            else if (color[temp] == color[i]) // если цвет совпадает, то граф уже не двудольный
                flag = false;
        }
    }
}

int main()
{
    ifstream fin("bipartite.in");
    ofstream fout("bipartite.out");
    int n, m, v1, v2;
    fin >> n >> m;
    g.resize(n); // заполняем вектора изначальными значениями
    color.assign(n, 0);
    for (int i = 0; i < m; i++) // считываем данные о вершинах
    { // и строим список смежности
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    for (int i = 0; i < n; i++)
        if (color[i] == 0)
            bfs(i);
    flag == true ? fout << "YES" : fout << "NO";
    return 0;
}