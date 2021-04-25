#include <fstream>
#include <vector>

using namespace std;

vector<int> NaiveStringMatcher(string t, string p)
{
    int n = t.size();
    int m = p.size();
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        if (t[i] == p[0])
        {
            if (m != 1)
                for (int j = 1; j < m; j++)
                {
                    if (t[i + j] == p[j])
                    {
                        if (j == m - 1)
                            ans.push_back(i);
                        continue;
                    }
                    else
                        break;
                }
            else
                ans.push_back(i);
        }
    }
    return ans;
}

int main()
{
    ifstream fin("search1.in");
    ofstream fout("search1.out");
    string p, t;
    fin >> p >> t;
    vector<int> ans;
    ans = NaiveStringMatcher(t, p);
    fout << ans.size() << endl;
    for (int i: ans)
    {
        fout << i + 1 << " ";
    }
    return 0;
}