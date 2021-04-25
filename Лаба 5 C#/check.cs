using System;
using System.IO;
using System.Collections.Generic;

// Console.ReadLine - scnaf, cin
// Console.WriteLine - printf, cout
// int.Parse - для преобразования строки в число
namespace Algosiki
{
	class Height_Lab1
	{
		public struct element
		{
			public int value;
			public int left;
			public int right;
		}
		static int check(List<int> tops)
		{
			for (int i = 1; i < tops.Count; i++)
			{
				if (tops[i] <= tops[i - 1])
					return 1;
			}
			return 0;
		}
		static void sort_tops(element[] tree, List<int> tops, int x)
		{
			if (x != -1)
			{
				sort_tops(tree, tops, tree[x].left);
				tops.Add(tree[x].value);
				sort_tops(tree, tops, tree[x].right);
			}

		}
		static int check_for_answer(element[] tree, int x)
		{
			List<int> tops = new List<int>();
			sort_tops(tree, tops, 0);
			return check(tops);
		}
		static int Main()
		{
			int n;
			element[] tree;
			using (var input = new StreamReader("height.in"))
			{
				n = int.Parse(input.ReadLine());
				tree = new element[n];
				if (n != 0)
				{
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
			}
			using (var output = new StreamWriter("height.out"))
			{
				if (n == 0 || check_for_answer(tree, 0) == 0)
					output.WriteLine("YES");
				else
					output.WriteLine("NO");
			}
			return 0;
		}
	}
}
