#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void LCS(int size1, int size2, string str1, string str2, vector<int>& lastMatrixStr)
{
    vector<vector<int>> k(2, vector<int>(size2 + 1));
    for (int j = 0; j <= size2; j++)
        k[1][j] = 0;
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j <= size2; j++)
            k[0][j] = k[1][j];
        for (int j = 1; j <= size2; j++)
        {
            if (str1[i] == str2[j - 1])
                k[1][j] = k[0][j - 1] + 1;
            else
                k[1][j] = max(k[1][j - 1], k[0][j]);
        }
    }
    for (int j = 0; j <= size2; j++)
        lastMatrixStr[j] = k[1][j];
}

void Hirschberg(int size1, int size2, string str1, string str2)
{
    if (size2 == 0)
        return;
    if (size1 == 1)
    {
        int f = str2.find_first_of(str1[0]);
        if (f != string::npos)
            cout << str1[0];
        return;
    }
    vector<int> l1(size2 + 1);
    vector<int> l2(size2 + 1);
    int mid = size1 / 2;
    LCS(mid, size2, str1.substr(0, mid), str2, l1);
    string str1_second = str1;
    string str2_second = str2;
    reverse(str1_second.begin(), str1_second.end());
    reverse(str2_second.begin(), str2_second.end());
    LCS(mid + 1, size2, str1_second.substr(0, size1 - mid), str2_second, l2);
    int maxV = l2[0], maxJ = 0;
    for (int j = 0; j <= size2; j++)
        if (l1[j] + l2[size2 - j] > maxV)
        {
            maxV = l1[j] + l2[size2 - j];
            maxJ = j;
        }
    if (!mid)
        mid++;
    if (l1[size2] > maxV)
        maxJ = size2;
    Hirschberg(mid, maxJ, str1.substr(0, mid), str2.substr(0, maxJ));
    Hirschberg(size1 - mid, size2 - maxJ, str1.substr(mid, size1), str2.substr(maxJ, size2));
}
int main()
{
    string str1, str2;
    cin >> str1 >> str2;
    Hirschberg(str1.length(), str2.length(), str1, str2);
    return 0;
}