#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

const int infinity = INT_MAX;
vector<vector<int>> g;

int main()
{
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");
    int n, m, v1, v2, w;
    fin >> n >> m;
    g.resize(n, vector<int>(n, infinity)); // заполняем граф изначально бесконечностями
    for (int i = 0; i < m; i++) // после заполняем матрицу весов
    {
        fin >> v1 >> v2 >> w;
        v1--, v2--;
        g[v1][v2] = w;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (g[i][k] < infinity && g[k][j] < infinity) // если вес меньше бесконечности
                    (g[i][k] + g[k][j]) > g[i][j] ? g[i][j] = g[i][j] : g[i][j] = (g[i][k] + g[k][j]); // выбираем минимум среди g[i][j] и g[i][l] + g[l][j]
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) // главную диагональ заполняем нулями
                g[i][j] = 0;
            fout << g[i][j] << " ";
        }
    fout << endl;
    }
    return 0;
}
