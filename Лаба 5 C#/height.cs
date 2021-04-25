using System;
using System.IO;

// Console.ReadLine - scnaf, cin
// Console.WriteLine - printf, cout
// int.Parse - ��� �������������� ������ � �����
namespace Algosiki
{
	class Height_Lab1
	{
		public struct element // ������ ��������� ��� ������� ��������
        { // ���� ������� ������ �� �� ��� ��� ���� ��������� ����� �������� �� �����
			public int value;
			public int left;
			public int right;
        }
		static int find_height(element []tree, int h) // ����������� ������� ������ ������
        {
			if (h == -1) // ���� ����-����� �� ����� ��������, �� ����� ��� ��� �����
				return 0; // ������ ����
			else
				return Math.Max(find_height(tree, tree[h].left), find_height(tree, tree[h].right)) + 1; // ������� ������ �������
		}
		static int Main()
		{
			int n;
			element[] tree; // ������ ���������
			using (var input = new StreamReader("height.in")) // ������ �� �����.in
            {
				n = int.Parse(input.ReadLine());
				tree = new element[n]; // �������� ���������, ��� ������ ����
				for (int i = 0; i < n; i++)
				{
					string[] line = input.ReadLine().Trim().Split();
					tree[i].value = int.Parse(line[0]);
					tree[i].left = int.Parse(line[1]);
					tree[i].right = int.Parse(line[2]);
					tree[i].right--;
					tree[i].left--;
				}
			}
			using (var output = new StreamWriter("height.out")) // ������ � �����.out
            {
				if (n == 0)
					output.WriteLine(0);
				else
					output.WriteLine(find_height(tree, 0));
			}
			return 0; 
		}
	}
}
