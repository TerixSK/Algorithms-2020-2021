#include <fstream>
#include <iostream>
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

vector<vector<int>> make_kmp(int a, string s)
{
    int n = s.size();
    vector<int> prefix = get_prefix(s);
    vector<vector<int>> ans(n + 1, vector<int>(a));
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < a; j++)
            if (i > 0 && j + 'a' != s[i])
                ans[i][j] = ans[prefix[i - 1]][j];
            else
                ans[i][j] = i + (j + 'a' == s[i]);
    return ans;
}

int main()
{
    //ifstream cin("in.in");
    //ofstream cout("out.out");
    string s;
    int a;
    cin >> a >> s;
    vector<vector<int>> kmp = make_kmp(a, s);
    for (auto & i: kmp)
    {
        for (int j: i)
            cout << j << " ";
        cout << endl;
    }
    return 0;
}