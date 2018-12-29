/*
filename: main.c
time: 2018.12.18
扫雷
M 雷

*/

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

#define SIZE 9		//雷区大小
#define NUM 10		//雷的个数



int main()
{

	void init(char euyul[SIZE][SIZE]);
	void output(char euyul[SIZE][SIZE]);
	char euyul[SIZE][SIZE];
	void play(char euyul[SIZE][SIZE]);
	//printf("%d\n", time());
	init(euyul);
	output(euyul);
	play(euyul);
//	output(euyul);
	return 0;
}

void init(char euyul[SIZE][SIZE])	//生成雷区
{
	void hint(char euyul[SIZE][SIZE]);		//生成提示数字
	int cow, low, i;
	int rand_cow, rand_low;
	for (cow = 0; cow < SIZE; cow++)
	{
		for (low = 0; low < SIZE; low++)
		{
			euyul[cow][low] = '0';
		}
	}
	srand((unsigned)(time(NULL)));
	for (i = 0; i < NUM; i++)		//放雷
	{
		rand_cow = rand() % 8;
		rand_low = rand() % 8;
		euyul[rand_cow][rand_low] = 'M';
	}
	hint(euyul);		//放入提示数字
}

void hint(char euyul[SIZE][SIZE])		//生成提示数字
{
	void judge(int cow,int low,char euyul[SIZE][SIZE]);		//判断周围有几个雷
	int cow, low;
	for (cow = 0; cow < SIZE; cow++)
	{
		for (low = 0; low < SIZE; low++)
		{
			if (euyul[cow][low] != 'M')judge(cow, low, euyul);
		}
	}
}

void judge(int cow,int low,char euyul[SIZE][SIZE])		//判断周围雷的个数
{
	char count = '0';
	int i, j, t, k;
	for (i = cow - 1, t = 0; t < 3; i++, t++)
	{
		for (j = low - 1, k = 0; k < 3; j++, k++)
		{
			if (i>=0 && j>=0 && euyul[i][j] == 'M')count++;
		}
	}
	euyul[cow][low] = count;
}

void print(char euyul[SIZE][SIZE])		//待判断雷区
{
	int cow, low;
	printf("\t");
	for (cow = 0; cow < SIZE; cow++)
	{
		printf("%d\t", cow);
	}
	printf("\n\n");
	for (cow = 0; cow < SIZE; cow++)
	{
		printf("%d\t", cow);
		for (low = 0; low < SIZE; low++)
		{
			printf("%c\t",euyul[cow][low]);
		}
		printf("\n\n");
	}
	
}
void output(char euyul[SIZE][SIZE])		//打印雷区
{
	int cow, low;
	printf("\t");
	for (cow = 0; cow < SIZE; cow++)
	{
		printf("%d\t", cow);
	}
	printf("\n\n");
	for (cow = 0; cow < SIZE; cow++)
	{
		printf("%d\t", cow);
		for (low = 0; low < SIZE; low++)
		{
			printf("%c\t", euyul[cow][low]);
		}
		printf("\n\n");
	}
}


/*
R：标记雷
L：点开（左键）
？：不确定
*/



void play(char euyul[SIZE][SIZE])
{
	void print(char euyul[SIZE][SIZE]);		//待判断雷区
	int M(int cow, int low, char euyul[SIZE][SIZE],char euy[SIZE][SIZE]);		//判断是否踩到雷
	void R(int cow, int low, char euyul[SIZE][SIZE], char euy[SIZE][SIZE]);
	void RR(int cow, int low, char euy[SIZE][SIZE]);
	clock_t t = clock();
	t = t / CLOCKS_PER_SEC;
	//printf("%d\n", t);
	int end(char euyul[SIZE][SIZE]);	//判断是否还有雷
	char euy[SIZE][SIZE];
	char scan;
	int cow, low;
	int dead = 1;
	for (cow = 0; cow < SIZE; cow++)
		for (low = 0; low < SIZE; low++)
			euy[cow][low] = '@';
	print(euy);
	while (dead)
	{

		while (1)	//输入用户选择，如果输入不正确继续输入
		{
			printf("标记雷:(X Y R),点开(X Y L)不确定(X Y ?)");
			if (scanf("%d %d %c", &cow, &low, &scan) == 3 && cow >= 0 && cow < SIZE&&low >= 0 && low < SIZE) break;
		}
		switch (scan)
		{
		case 'R':R(cow, low, euyul, euy); break;
		case 'L':dead = M(cow, low, euyul, euy); break;
		case '?':RR(cow, low, euy); break;

		}
		if (!end(euyul)) break;
		system("cls");
		print(euy);


	}
	if (dead == 1)
	{
		t = clock();
		t = t / CLOCKS_PER_SEC;
		printf("你赢了,耗时：%d s",t);

		system("pause");
	}
	else
	{
		system("cls");
		output(euyul);
		printf("you lose！");
		system("pause");
	}
	
	
}

void R(int cow, int low, char euyul[SIZE][SIZE], char euy[SIZE][SIZE])
{
	euy[cow][low] = 'M';
	if (euyul[cow][low] == 'M')
	{
		euyul[cow][low] = '0';
		//equ = 
	}

}

int M(int cow,int low,char euyul[SIZE][SIZE],char euy[SIZE][SIZE])		//判断是否踩到雷
{
	int rand_scan = 0;
	int i, j, k;
	if (euyul[cow][low] == 'M')   return 0;
	else
	{
		rand_scan = rand() % 7+1;		//每次左键最多点开
		for(i=cow-1;i<rand_scan;i++)
			for (j = low - 1; j < rand_scan; j++)
			{
				if (euyul[i][j] != 'M') euy[i][j] = euyul[i][j];
			}
		return 1;
	}
}
void RR(int cow, int low, char euy[SIZE][SIZE])
{
	euy[cow][low] = '?';
}
int end(char euyul[SIZE][SIZE])	//判断是否还有雷
{
	int i, j;
	int coun = 0;
	for(i=0;i<SIZE;i++)
		for (j = 0; j < SIZE; j++)
		{
			if (euyul[i][j] == 'M') coun++;
		}
	if (coun == 0) return 0;
	else return 1;
}



/*
2018.12.18 23：48
基本好了 玩的时候应该还有一点小bug
点开L时有时不一定会死
睡觉
2018.12.19 23:56
测试暂无bug
增加了显示完成时间

*/