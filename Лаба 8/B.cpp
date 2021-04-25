#include <fstream>
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    fin >> n;
    int arr[n][n], check = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fin >> arr[i][j];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ( (arr[i][j] == 1 && arr[j][i] == 0)
            || ( (arr[i][j] == 1 && arr[j][i] == 1)
            && i == j) )
                check = 1;
        }
    }
    if (check == 0)
        fout << "YES";
    else
        fout << "NO";
    return 0;
}