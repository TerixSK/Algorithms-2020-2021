#include <fstream>
#include <vector>

using namespace std;

vector<int> get_prefix(string str)
{
    int n = str.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++)
    {
        int k = p[i - 1];
        while (k > 0 & str[i] != str[k])
            k = p[k - 1];
        if (str[i] == str[k])
            k++;
        p[i] = k;
    }
    return p;
}

int main()
{
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");
    string str;
    fin >> str;
    vector<int> p = get_prefix(str);
    for (int i: p)
        fout << i << " ";
    return 0;
}