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

vector<int> kmp(string p, string t)
{
    int n = t.size();
    int m = p.size();
    vector<int> ans;
    vector<int> prefix = get_prefix(p + "#" + t);
    for (int i = 0; i < n; i++)
        if (prefix[m + i + 1] == m)
            ans.push_back(i - m + 2);
    return ans;
}

int main()
{
    ifstream fin("search2.in");
    ofstream fout("search2.out");
    string p, t;
    fin >> p >> t;
    vector<int> ans = kmp(p, t);
    fout << ans.size() << endl;
    for (int i: ans)
        fout << i << " ";
    return 0;
}