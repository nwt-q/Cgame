#include<stdio.h>
#include<stdlib.h>

char Arr[15][15] = { 0 };//���Ӧ��������
char X = 0, Y = 0; //�Ҳ���������������
char Now = -1;     //�����洢ʲô����

char print(char n); //��ӡ����
void show(void); //��ʾ����//�Ҳ����-���Ǵ�ӡ����
void act(void);  //��Ϊ
int judge(int a, int b);  //�����ʲô?�ж�?�ж�ʲô?

int main(int argc, const char* argv[]) {
	system("title  5����");
	system("mode con cols=64 lines=32");
	system("color E0");
	while (1) {
		show();
		if (!(judge(0, 1) || judge(1, 0) || judge(1, -1) || judge(1, 1)))//������
			Now = -Now; //���ʲô?//ŶŶŶ�Ե���5�����ӵ�ʱ������?
		else
			return 0;
		act(); //???
	}
}

char print(char n) { //????
	char ch = ' ';  //????
	switch (n)
	{
	case 0:ch = '$'; break;//����ո�
	case 1:ch ='X'; break;// ������������
	case -1:ch = '#'; break;// ������������
	}
	return ch; //???
}

void show(void)
{
	system("cls");//�����ǰ����
	printf(" ");
	for (int i = 0; i < 15; i++)
	{//???????
		printf(" %2d", i); //��ӡ������
	}
	printf("\n");
	for (int i = 0; i < 15; i++) {
		printf("%2d ", i);  //��ӡ������
		for (int j = 0; j < 15; j++)
		{
			printf(" %c ", print(Arr[i][j]));
		}
		printf("\n");
	}
}

void act(void)
{
	printf("������%c��������:", print(Now));
	scanf_s("%hhd%hhd", &X, &Y);
	if (!(X >= 0 && X < 14 && Y >= 0 && Y <= 14 && Arr[X][Y] == 0))//�߽��ж�
	{
		printf("������������,�����¿�ʼ��Ϸ:\n");
		exit(NULL);
		act();//�������е����emm
	}
	else
	{
		Arr[X][Y] = Now;//�������ӵ�λ��
	}
}

int judge(int a, int b) //�ж��Ƿ�����5����?
{
	int cunt = 1;
	for (int i = -4; i <= 4; i++)
	{
		if (X + i < 0 || Y + i < 0)
		{
			continue;//����?
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
			print("%c���ʤ", print(Now));
			return Now;
		}
	}
	return 0;
}

