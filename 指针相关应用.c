#include<stdio.h>  
#include<stdlib.h>  
#include<windows.h>  

//int main() {
//	int a, b;
//	a = 1;
//	while (a <= 2) {
//		system("cls");
//		b = 1;
//		if(b <= a) {
//			printf("  ");
//			b++;
//		}
//		printf(" O\n");
//		b = 1;
//		if(b <= a) {
//			printf("  ");
//			b++;
//		}
//		printf("<H>\n");
//		b = 1;
//		if(b <= a) {
//			printf("  ");
//			b++;
//		}
//		printf("I I\n");
//		Sleep(1);
//		system("cls");
//	}
//	return 0;
//}

int main() {
	int a[] = { 1,2,3,4,5,6 };
	int *p = &a[3];
	printf("%d\n", *&p[-1]);//vsstdio可能无法进行*P[-1],但是我们可以对P[-1]进行计算然后得值在对P的指针进行简引用*(p-1)==*&p[-1]
	printf("%d %d\n",p[2],a[5]);


	//malloc()动态内存分配空间产生数组
	int* g;
	int SIZE;
	int* b;
	b = &SIZE;
	scanf_s("%d", b);//输入数组大小
	//malloc分配空间有限制超出便会失败,所以要free()
	//可以free(NULL)free后在free会导致程序出错
	g = (int*)malloc(SIZE * sizeof(int));//此时g为一个数组//这个可以让我们充分理解数组
	//用sizeof()分配int大小的空间,在乘以要存储数组的数量即可得到数组的存储大小,然后转换为int*类型然后存储在g中
	int* q;
	q = g;
	for (int i=0;i<SIZE;i++) {
		scanf_s("%d", q+i);//scanf中q+i为取地址不是*(p+i)
	}
	for (int i = 0; i <SIZE; i++) {
		printf("%-2d", *&(q[i]));//for (int i = 0; i <*g; i++)//这样输出的是第一个元素不是i<*g小于第一个元素所以才只输出一个
		/*printf("%d ", *(q++));*/
	}
	free(g);//不能忘记释放空间
	system("pause");
	return 0;
}
//#include <stdio.h>  
//#include <stdlib.h>  
//
//int main() {
//    int* g;
//    int SIZE;
//    int* b;
//    b = &SIZE;
//    scanf_s("%d", b); // 输入数组大小  
//    g = (int*)malloc((SIZE + 1) * sizeof(int)); // 多分配一个空间用于存储元素数量  
//    if (g == NULL) {
//        printf("Memory allocation failed!\n");
//        return 1; // 返回错误代码  
//    }
//    int* q = g;
//    *q = SIZE; // 在数组的第一个位置存储元素数量  
//    q++; // 指向数组的第二个位置，用于存储实际元素  
//
//    // 读入数组元素  
//    for (int i = 0; i < SIZE; i++) {
//        scanf_s("%d", q + i);
//    }
//
//    // 打印数组元素  
//    for (int i = 0; i < *g; i++) { // 通过*g获取元素数量  
//        printf("%d ", *(q + i));
//    }
//    printf("\n");
//
//    free(g); // 释放内存空间  
//    system("pause"); // 暂停程序执行，等待用户按键后继续执行程序  
//    return 0; // 返回0表示程序正常退出  
//}
