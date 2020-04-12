#include"calculate.h"

void rof(result* result)
{
	for (int i = 20;i > 1;i--)
	{
		if (result->up % i == 0 && result->down % i == 0)
		{
			result->up /= i;
			result->down /= i;
			if (result->down == 1)
			{
				result->down = 0;
				result->up = 0;
				result->real = result->up;
			}
		}
	}
}

void creat(int num, int range)
{
	FILE* file1;
	FILE* file2;
	errno_t err;
	err = fopen_s(&file1, "Exercises.txt", "w");
	if (err != 0)
	{
		printf("文件打开失败！");
	}
	err = fopen_s(&file2, "Answers.txt", "w");
	if (err != 0)
	{
		printf("文件打开失败！");
	}

	else
	{
		int count;
		int NO = 1;
		srand(time(NULL));

		while (NO <= num)
		{
			std::stack<int> eq[4];
			std::stack<char> sym[12];
			int n[12] = {};
			char s[12] = {};
			int j = 0, k = 0, l = 0;
			count = (rand() % 3) + 2;
			count = 2 * count - 1;
			fprintf(file1, "%d. ", NO);

			for (int i = 0;i < count;i++)
			{
				if (i % 2 == 0 && (rand() % 2) && j == 0 && (i != count - 1))
				{
					s[i] = '(';
					k = 1;
					if (i == 0)l = 1;
				}
				if (i % 2 == 0)
				{
					n[i] = rand() % range;
				}
				if (i == count - 3 && j == 1 && l == 1)
				{
					s[i] = ')';
					j = 0;
					l = 0;
				}
				if (i == count - 1 && j == 1)
				{
					s[i] = ')';
					j = 0;
				}
				if (i % 2 == 0 && (rand() % 2) && j == 1)
				{
					s[i] = ')';
					j = 0;
				}
				if (i % 2 == 1)
				{
					int ran = rand() % 4;
					switch (ran)
					{
					case 0:s[i] = '+';break;
					case 1:s[i] = '-';break;
					case 2:s[i] = '*';break;
					case 3:s[i] = '/';break;
					}
				}
				if (k == 1)
				{
					j = 1;
					k = 0;
				}
			}

			for (int i = 0;i < count;i++)
			{
				if (s[i] == '-' && s[i + 2] == '*')s[i] = '+';
				if (s[i + 1] == '-' && s[i + 2] != '(' && s[i] != ')')
				{
					if (n[i] < n[i + 2])
					{
						n[i] += n[i + 2];
						n[i + 2] = n[i] - n[i + 2];
						n[i] = n[i] - n[i + 2];
					}
					fprintf(file1, "%c", s[i]);
					fprintf(file1, "%d", n[i]);
				}
				else if (s[i] == '*')fprintf(file1, " × ");
				else if (s[i] == '/')fprintf(file1, " ÷ ");
				else if (s[i + 1] == '/' && n[i] == 0)
				{
					n[i] += 1;
					fprintf(file1, "%d", n[i]);
				}
				else if (s[i] == ')')
				{
					fprintf(file1, "%d", n[i]);
					fprintf(file1, "%c", s[i]);
				}
				else if (s[i] == '(')
				{
					fprintf(file1, "%c", s[i]);
					fprintf(file1, "%d", n[i]);
				}
				else if (i % 2 == 0)fprintf(file1, "%d", n[i]);
				else fprintf(file1, " %c ", s[i]);
			}

			fprintf(file1, " = \n");

			struct result result;
			struct result* p = &result;
			result.real = -1;
			result.up = 0;
			result.down = 0;

			for (int i = 0;i < count;i++)
			{
				int wait = 0, logic = 0;
				char s1[3] = {};
				if (i % 2 == 0)eq->push(n[i]);
				if (i != 0)
				{
					if ((s[i - 1] == '+' || s[i - 1] == '-') && i % 2 == 0)
					{
						s1[wait] = s[i - 1];
						wait++;
					}
					else if (s[i - 1] == '*' || s[i - 1] == '/')calculate(eq, s[i - 1], p);
				}
				if (s[i] == '(')logic = i;
				else if (s[i] == ')')
				{
					for (int cal = i - 1;cal > logic;cal--)
					{
						if (s[cal] == '+' || s[cal] == '-')
						{
							calculate(eq, s[cal], p);
							wait--;
						}
					}

				}
				if (i == count - 1 && wait != 0)
				{
					int c = 0, d = 0;
					switch (wait)
					{
					case 1:calculate(eq, s1[0], p);break;
					case 2:c = eq->top();eq->pop();calculate(eq, s1[0], p);eq->push(c);calculate(eq, s1[1], p);break;
					case 3:
						c = eq->top();
						eq->pop();
						d = eq->top();
						eq->pop();
						calculate(eq, s1[0], p);
						eq->push(d);
						calculate(eq, s1[1], p);
						eq->push(c);
						calculate(eq, s1[2], p);
						break;
					default:break;
					}
				}
			}
			if (result.up != 0)rof(p);
			if (result.up == 0)
				fprintf(file2, "%d. %d\n", NO, result.real);
			else if (result.real == 0)
				fprintf(file2, "%d. %d/%d\n", NO, result.up, result.down);
			else
				fprintf(file2, "%d. %d'%d/%d\n", NO, result.real, result.up, result.down);
			NO++;
		}
	}
}

void calculate(std::stack<int>* eq, char sym, struct result* result)
{
	if (result->real == -1)
	{
		int a = eq->top();
		eq->pop();
		int b = eq->top();
		eq->pop();
		switch (sym)
		{
		case '+':result->real = a + b;break;
		case '-':result->real = b - a;break;
		case '*':result->real = a * b;break;
		case '/':
		{
			if (b % a == 0)
				result->real = b / a;
			else if (b < a)
			{
				result->up = b;
				result->down = a;
				result->real = 0;
			}
			else
			{
				result->real = b / a;
				result->up = b - a * result->real;
				result->down = a;
			}
			break;
		}
		}
	}
	else
	{
		int a = eq->top();
		eq->pop();
		switch (sym)
		{
		case '+':result->real += a;break;
		case '-':result->real -= a;if (result->real < 0)result->real = -result->real;break;
		case '*':
		{
			if (result->up == 0)
			{
				result->real *= a;
			}
			else 
			{
				result->up *= a;
				if ((result->up) % (result->down) == 0)
				{
					result->real = result->up / result->down;
					result->up = 0;
					result->down = 0;
				}
				else if (result->up > result->down)
				{
					result->real += (result->up / result->down);
					result->up -= result->down * ((result->up / result->down));
				}
			}
			break;
		}
		case '/':
		{
			if (result->up == 0)
			{
				if (a % result->real == 0)
					result->real = a / result->real;
				else
				{
					result->up = result->real;
					result->real = 0;
					result->down = a;
					if (result->up > result->down)
					{
						result->real = result->up / result->down;
						result->up -= result->down * (result->up / result->down);
					}
				}
			}
			else
				result->down *= a;
			break;
		}
		}
	}
}

void verify()
{
	int num = 0;
	FILE* filea;
	FILE* fileb;
	errno_t err;
	err = fopen_s(&filea, "Exercises.txt", "r");
	if (err != 0)
	{
		printf("文件打开失败！");
	}
	err = fopen_s(&fileb, "Answers.txt", "r");
	if (err != 0)
	{
		printf("文件打开失败！");
	}
	int in = 0, r = 0, w = 0;
	int wrong[10000] = {};
	int right[10000] = {};
	while (!feof(filea))
	{
		if (fgetc(filea) == '\n')
			num++;
	}
	fclose(filea);
	err = fopen_s(&filea, "Exercises.txt", "r");
	if (err != 0)
	{
		printf("文件打开失败！");
	}
	while (in < num)
	{
		int rig = 1;
		while (fgetc(filea) != '=');
		while (fgetc(fileb) != '.');
		fgetc(filea);
		fgetc(fileb);
		for (;fgetc(filea) != '\n';)
		{
			if (fgetc(filea) == fgetc(fileb))continue;
			else
			{
				rig = 0;
				break;
			}
		}
		if (rig == 0)
		{
			right[r] = in;
			r++;
		}
		else if (rig == 1)
		{
			wrong[w] = in;
			w++;
		}
		in++;
	}
	FILE* file;
	err = fopen_s(&file, "Grade.txt", "w");
	if (err != 0)
	{
		printf("文件打开失败！");
	}
	if (r == 0)
		fprintf(file, "Correct:0 ( )\n");
	else
	{
		fprintf(file, "Correct:%d (%d", r, right[0] + 1);
		for (int i = 1;i < r;i++)
		{
			fprintf(file, ", %d", right[i] + 1);
		}
		fprintf(file, ")\n");
	}
	if (w == 0)
		fprintf(file, "Wrong:0 ( )\n");
	else
	{
		fprintf(file, "Wrong:%d (%d", w, wrong[0] + 1);
		for (int i = 1;i < w;i++)
		{
			fprintf(file, ", %d", wrong[i] + 1);
		}
		fprintf(file, ")\n");
	}
}
