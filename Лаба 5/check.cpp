#include <fstream>
#include <vector>

using namespace std;

struct element // ������ ��������� ��� �������� ��������
{
	int value; // ���� �����
	int left; // ������ ������ ������
	int right; // ������ ������� ������
};

int check(vector <int>& tops) // ����������� ������� �������� �����������
{
	for (int i = 1; i < tops.size(); i++) // ��������� ��� ������� � ���� ����� �� ������� ������, ��� ���������, �� ������ ��� �����������
	{
		if (tops[i] <= tops[i - 1])
			return 1; //  ����, ������������ ������ �� ������ �������� ������������
	}
	return 0; // ���� ��� ������� ������ ��������, �� ������� ����, ������������, ��� �� ��
}

void sort_tops(element* tree, vector <int>& tops, int x) // ����������� ������� ������ ���������� ������
{
	if (x != -1) // ���� � ������� ��� ������, �� ������ ������� �� ���
	{
		sort_tops(tree, tops, tree[x].left);  // ��������� �������� ��� ������ ������ 
		tops.push_back(tree[x].value);		  // �������� ������� � ������
		sort_tops(tree, tops, tree[x].right); // ��������� �������� ��� ������� ������  
	}
}

int check_for_answer(element* tree, int x)
{
	vector <int> tops; // ������ ������, ������� ����� ������� ������� ������
	sort_tops(tree, tops, 0); // ��������� ������ ����������
	return check(tops);
}

int main()
{	
	ifstream fin("check.in");
	ofstream fout("check.out");
	int n;
	fin >> n;
	element* tree = new element[n];
	for (int i = 0; i < n; i++)
	{
		fin >> tree[i].value >> tree[i].left >> tree[i].right;
		tree[i].left--;
		tree[i].right--;
	}

	if (n == 0 || check_for_answer(tree, 0) == 0) // ���� ���� - ok ��� ������ �� �������� ���������, �� ������� "YES"
		fout << "YES";
	else
		fout << "NO";

	fin.close();
	fout.close();
	return 0;
}