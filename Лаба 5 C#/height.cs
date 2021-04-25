using System;
using System.IO;

// Console.ReadLine - scnaf, cin
// Console.WriteLine - printf, cout
// int.Parse - дл€ преобразовани€ строки в число
namespace Algosiki
{
	class Height_Lab1
	{
		public struct element // —оздаЄм структуру дл€ каждого элемента
        { // надо ху€рить публик по кд ибо без этой махинации ниху€ работать не будет
			public int value;
			public int left;
			public int right;
        }
		static int find_height(element []tree, int h) // Ќевъебенна€ функци€ ху€рит высоту
        {
			if (h == -1) // если Єбик-папка не имеет пиздюков, то нахуй оно нам нужно
				return 0; // ху€рим попу
			else
				return Math.Max(find_height(tree, tree[h].left), find_height(tree, tree[h].right)) + 1; // подсчЄт длинны пиписки
		}
		static int Main()
		{
			int n;
			element[] tree; // ху€рим массивчик
			using (var input = new StreamReader("height.in")) // чтени€ из жопку.in
            {
				n = int.Parse(input.ReadLine());
				tree = new element[n]; // доху€рим массивчик, дл€ балдЄжа жопы
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
			using (var output = new StreamWriter("height.out")) // запись в жопку.out
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
