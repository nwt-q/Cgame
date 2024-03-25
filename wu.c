#include<stdio.h>
#include<stdlib.h>

char Arr[15][15] = { 0 };//这个应该是棋盘
char X = 0, Y = 0; //我猜这个是输入的坐标
char Now = -1;     //用来存储什么棋子
char print(char n); //打印棋盘
void show(void); //显示棋盘//我猜这个-就是打印棋盘
void act(void);  //行为
int judge(int a, int b);  //这个是什么?判断?判断什么?

int main(int argc, const char* argv[]) {
	system("title  5子棋");
	system("mode con cols=64 lines=32");
	system("color E0");
	while (1) {
		show();
		if (!(judge(0, 1) || judge(1, 0) || judge(1, -1) || judge(1, 1)))//对整体
			Now = -Now; //这个什么?//哦哦哦对当有5个棋子的时候消除?
		else
			return 0;
		act(); //???
	}
}

char print(char n) { //????
	char ch = ' ';  //????
	switch (n)
	{
	case 0:ch = '$'; break;//代表空格
	case 1:ch ='X'; break;// 代表棋子类型
	case -1:ch = '#'; break;// 代表棋子类型
	}
	return ch; //???
}

void show(void)
{
	system("cls");//清除当前缓存
	printf(" ");
	for (int i = 0; i < 15; i++)
	{//???????
		printf(" %2d", i); //打印行坐标
	}
	printf("\n");
	for (int i = 0; i < 15; i++) {
		printf("%2d ", i);  //打印列坐标
		for (int j = 0; j < 15; j++)
		{
			printf(" %c ", print(Arr[i][j]));
		}
		printf("\n");
	}
}

void act(void)
{
	printf("请输入%c棋子坐标:", print(Now));
	scanf_s("%hhd%hhd", &X, &Y);
	if (!(X >= 0 && X < 14 && Y >= 0 && Y <= 14 && Arr[X][Y] == 0))//边界判断
	{
		printf("输入坐标有误,请重新开始游戏:\n");
		exit(NULL);
		act();//程序运行的入口emm
	}
	else
	{
		Arr[X][Y] = Now;//放置棋子的位置
	}
}

int judge(int a, int b) //判断是否满足5个子?
{
	int cunt = 1;
	for (int i = -4; i <= 4; i++)
	{
		if (X + i < 0 || Y + i < 0)
		{
			continue;//跳过?
		}
		if (X + i >= 14 || Y + i >= 14)
		{
			break;
		}
		if (Arr[X + i * a][Y - i * b] == Now && Arr[X + (i + 1) * a][Y - (i + 1) * b]== Now)
		{
			cunt++;
		}
		else
		{
			cunt = 1;
		}
		if (cunt >= 5)
		{
			print("%c棋获胜", print(Now));
			return Now;
		}
	}
	return 0;
}

