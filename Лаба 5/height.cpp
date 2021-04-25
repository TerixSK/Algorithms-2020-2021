#include <fstream>
#include <algorithm>

using namespace std;

struct element // ������ ��������� ��� �������� ��������
{
	int value; // ���� �����
	int left; // ������ ������ ������
	int right; // ������ ������� ������
};

/* �� ���������� �� �������� ���. ������ � ������������� ������ �� ��������, ������� ����� �����.
* ���� ����� ���, �� �� �� ����������. � ����� ����� �� ��������� ����� �� �������� ����������� �� ���� ������ ��� 
* �������� � height(������) + 1 �� ������ ����. ���������� �� �� ���� ��������, � ����� ��������� ������� ����� �������� �� ����� �����������.
*/

int find_height(element* tree, int h) // ���������� ������� ������ ������ ��������� ������
{
	if (h == -1) // ���� � �������� ��� �����, �� ����� �� ����������
		return 0;
	else  // ���� ���� ���� �� �� ���������� � ������������ ����� ��� �������
		return max(find_height(tree, tree[h].left), find_height(tree, tree[h].right)) + 1; // �� ������ ������������� �������� ������ max + 1
}

int main()
{
	ifstream fin("height.in");
	ofstream fout("height.out");
	int n;
	fin >> n;
	element* tree = new element[n];
	for (int i = 0; i < n; i++)
	{
		fin >> tree[i].value >> tree[i].left >> tree[i].right;
		tree[i].left--;
		tree[i].right--;
	}
	if (n == 0) // ���� ��������� � ������ ���, �� ������ ����� ����
		fout << 0;
	else
		fout << find_height(tree, 0) << endl; // ����� ���� ������
	fin.close();
	fout.close();
	return 0;
}