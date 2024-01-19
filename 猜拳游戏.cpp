#include<iostream>
#include<time.h>
using namespace std;

void cmp(int R, int x) {
	int y = 0;
	if (R == x) {
		y = 1;
	}
	else if (R == 1&&x==2||R==2&&x==3||R==2&&x==1) {
		y = 2;
	}
	else {
		y = 3;
	}
	switch (y) {
	case 1:
		cout << "平手\n";
		break;
	case 2:
		cout << "你赢了\n";
		break;
	case 3:
		cout << "你输了\n";
		break;

	}
}

int main() {
	int x = (std::rand() % (90)) + 1;
	string D;
	if (x >= 1 && x < 30) {
		D = "石头";
		x = 1;
	}
	else if (x >= 30 && x < 60) {
		D = "剪刀";
		x = 2;
	}
	else {
		D = "布";
		x = 3;
	}

	cout << "猜拳游戏\n"
		<< "~~~~~~~~~开始~~~~~~~~~\n"
		<< "请输入你的石头剪刀布:";

	string  R("");
	cin >> R;
	if (R == "剪刀") {
		int y = 2;
		cout << "电脑出的是:" << D << "\n";
		cmp(y, x);
	}
	else if (R == "石头") {
		int y = 1;
		cout << "电脑出的是:" << D << "\n";
		cmp(y, x);
	}
	else if (R == "布") {
		int y = 3;
		cout << "电脑出的是:" << D << "\n";
		cmp(y, x);
	}
	else {
		cout << "输入错误失败\n";
	}
	
}
