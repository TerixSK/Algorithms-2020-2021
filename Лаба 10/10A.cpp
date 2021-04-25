#include <fstream>
#include <vector>

using namespace std;

vector<int> deg;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m, v1, v2;
    fin >> n >> m;
    deg.assign(n, 0);
    for (int i = 0; i < m; i++) // считываем данный
    {
        fin >> v1 >> v2;
        v1--;
        v2--;
        deg[v1]++; // добовляем +1 к степени
        deg[v2]++;
    }
    for (auto i: deg) // вывод
        fout << i << " ";
    return 0;
}
