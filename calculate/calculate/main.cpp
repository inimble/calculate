#include"calculate.h"

int main(int argc,char *argv[])
{
	if (argc < 5)
	{
		printf("输入有误！");
		return 0;
	}

	else if(argv[1][1] != 'e')
	{
		int num = 0, range = 0;
		if (argv[1][1] == 'n' && argv[3][1] == 'r')
		{
			num = atoi(argv[2]);
			range = atoi(argv[4]);
		}
		else if (argv[1][1] == 'r' && argv[3][1] == 'n')
		{
			range = atoi(argv[2]);
			num = atoi(argv[4]);
		}
		else if (num == 0 || range == 0)
		{
			printf("输入的题目数量或范围有误！");
			return 0;
		}
		else
		{
			printf("输入有误！");
			return 0;
		}
		creat(num, range);

	}

	else if (argv[1][1] == 'e' && argv[3][1] == 'a')
	{
		verify();
	}
	system("pause");
}