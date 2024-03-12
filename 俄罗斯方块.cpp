
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h> 
#include<Mmsystem.h>
#pragma comment (lib,"winmm.lib")
#include<easyx.h>
#define CONST_ROW 23
#define CONST_COL 15//地图大小的变化
using namespace std;
// -------------------- 数据设计 --------------------
/*
    游戏界面
    map[i][j]表示坐标（i，j）的值
    空地为0
    静止实物小方块为1
    移动下落方块根据其种类分别由ABCDEFG表示
    A----T型方块
    B----L型方块
    C----Z型方块
    D----反L型方块
    E----反Z型方块
    F----长条型方块
    左右两侧的墙壁为2
    底侧的墙壁为3
    顶部的墙壁为4
    地图上面留出上面五行作为重开/设置/暂停/积分/计时等功能的实现页面
    有两行两列是墙壁的所在，所以真正的游戏界面是20*10的矩形，在设计模块时需要注意！！！！！！
    下面22*12的区域命名为游戏区
    上面5*12的区域命名为功能区
*/

//表示游戏过程中累计的积分
int score;

//达成胜利条件的设定分数，不用发生变化
int setscore=20000;

int gameSpeed = 1; //全局变量

//方块旋转时放在矩阵中转置，由此结构体确定矩阵的基准
struct matrix
{
    int x;
    int y;//基准点的坐标
};

//表示下落方块一次运动的的格子数，初始值为1，可在设置的难度中进行调整

//表示一次消除的行数

/*
flag变量: 标识接下来要跳转的界面
controller函数: 判断flag的值 来调用对应界面
View函数: 要跳转其它界面时 设置flag的值 并结束当前界面
参考：《项目常用思路-页面切换》
*/
int flag = 0;

int map[CONST_ROW][CONST_COL];
bool update = true;//更新判断
const int speednormal = 500, speedquick = 50;//速度数值设置
int speed = speednormal;
int num = 0;//新数据成员：记录方块执行fall函数的次数，从而判断方块是否可以下落来判断失败与否
matrix smallblocks[4];//新数据成员：储存四个方块的坐标
// -------------------- 数据设计 --------------------


// ---------------------service --------------------
/*
负责人：书山
功能：方块的自动下落
检测游戏界面上面的下落方块，将其的值传递到下一个格子中
参数：void
返回值：void
*/
void fall();

/*
负责人：书山
功能：使满足条件的下落方块变为静止方块
参数：void
返回值：void
*/
void crash();


/*
负责人：书山
功能：判定变为静止方块的条件
判定下落方块和静止方块是否接触，判定方块和底侧墙壁是否接触
参数：void
返回值：void
*/
bool judge();

/*
负责人：瑾言
功能：方块的刷新
使用rand函数随机生成一种方块，在画面上面没有下落方块（即值为ABCDEFG的小方块时）从地图中央掉落
switch（i）
刷新的方块可以从功能区生成之后开始掉落
参数：void
返回值：void
*/
void next();

/*
负责人：leo
功能：方块的消除
当方块嵌合碰撞之后构成成行的静止小方块时自动消除，然后上方的方块掉落
先把需要消除的一行赋值为0，在把上一行的静止小方块赋值到0行，重复向上实施值传递的操作
参数：void
返回值：void
*/
void eliminate();

/*
负责人：leo
判断在消除操作之后是否会有悬空的小方块需要下落
*/
bool decide(int i,int j);

/*
负责人：leo
将悬空的小方块落到下面
*/
void drop(int i, int j);

/*
（死亡界面对应的flag的值为3）
负责人：6
功能：死亡判断
当累计的静止方块和顶部的墙壁接触时游戏结束，跳转至死亡界面
参数：void
返回值：void
*/
void died();

/*
（胜利界面对应的flag的值为4）
负责人：瑾言
功能:胜利判断
得到的积分超过设置的分数，游戏胜利，跳转至胜利界面
参数：void
返回值：void
*/
void win();

/*
负责人：6
功能：实现页面的跳转
switch(flag)
{
case 1:
case 2:
····
}
在能够引起界面跳转的页面中改变flag的值，在使用本函数实现页面的跳转
在跳转完成之后要把flag的值回复为0.方便下一次跳转操作
参数：void
返回值：void
*/
void page();

/*
负责人：小斌
（难点）
游戏操作中w切换姿态
在游戏中按下w会切换方块的姿态
利用方块数据的转置来完成
使用上面的结构体定下转置的基准
游戏操作中s快速下落
按下s之后speed变为原来的三倍
speed=speed*3
游戏操作中按下a方块向左移动
方块的数据的传递
游戏操作中按下d方块向右移动
方块的数据的传递
*/
void playoperate();
void rotate();
void gotoXY(int x, int y);
void SetColor(int color);
void updateWindow();

/*
负责人：繁星
在菜单操作中按下w向上选择功能模块
在菜单操作中按下s向上选择功能模块
使用光标选择实现
在设置界面按下a向左切换数据，在设置界面按下d向右切换数据
int t=0；按下左键t加1，按下右键t减1
switch(t)
{

}
*/

/*
负责人：糕手
在游戏界面中不同的值对应不同的功能
按下之后启动相应的功能
按1暂停游戏
按2重新开始游戏
按3回到主界面
*/
void gamefuction();
void moveLeftRight(int offset);
// -------------------- service --------------------



// -------------------- view --------------------

/*
（游戏主界面对应的flag的值为1）
负责人：陆叁
初始的菜单界面
显示俄罗斯方块的游戏名字，然后下面有各种可供选择的界面进行跳转
（提示用户如何操作）
1.开始游戏
2.游戏设置
3.游戏说明
4.排行榜
5.退出游戏
*/
void menuview();

/*
放在最后全部人一起做
（对应的flag值为6）
游戏说明界面
向用户介绍游戏规则和制作游戏的图灵007小组（由大家共同完成）
选择回到主界面
*/
void gameexplain();

/*
（难点）
负责人：繁星
设置光标信息
头文件: #include<windows.h>
BOOL SetConsoleCursorPosition(句柄, 坐标);
句柄通过getStdHandle来获取即可
参考《c++项目控制台常用操作》
参数：void
返回值；void
*/


/*
（难点）
（游戏界面对应的flag的值为2）
负责人：糕手
游戏界面
接受键盘操作（提示用户如何操作）
1.地图和方块，玩家在地图里面操作游戏
2.暂停游戏（暂停之后可以选择重新开始游戏/返回主界面/继续游戏）
3.显示游戏积分
4.根据游戏地图中的情况跳转胜利界面或者死亡界面
5.显示游戏时间
参数：void
返回值；void
*/
void gameview();

/*
（难点）
负责人：小朱
从开始游戏时开始计时并实时显示在游戏界面中
游戏时间每增加两分钟，speed的值增加1
参数：void
返回值；void
*/
void gametime();

/*
负责人：小朱
累计游戏积分
当画面中有消除操作时加分，消除一行加1000（一次性消除两行给2400）然后更改游戏页面中对应的分数，在游戏结束之后将积分传入排行榜中
score=score+1000；
参数：void
返回值；void
*/

/*
负责人：6
游戏死亡界面
接受键盘操作，点击跳转至相关界面
int i=1;
输入w，i+=1，if（i<0）i+=3
输入s，i-=1
switch()
1.重新开始游戏
2.返回主界面
3.退出游戏
参数：void
返回值：void
*/
void diedview();

/*
负责人：瑾言
接受键盘，点击w/s切换至至相关界面
int i=1;
输入w，i+=1，if（i<0）i+=3
输入s，i-=1
switch()
1.重新开始游戏
2.返回主界面
3.退出游戏
参数：void
返回值：void
*/
void winview();

/*
（难点）
负责人：繁星/小斌
游戏操作
接受玩家的键盘输入： W和S，A和D
运用_kbhit()判断是否有键盘输入  注：当没有键盘输入时，_kbhit()默认值是0
运用_getch()实现操作
按下w，方块切换姿态，值传递，类似于矩阵转置
（所有方块都可以放在4*4的大正方形中，在正方形内变化相应的x、y坐标）
根据上方的结构体来找到大正方形
注：转置之后可能会挤压到静止方块
按下s，方块快速下落（将speed的值变为3倍）
按下a，方块向左移动一格，值向左传递，类似于方块的下落的结构
按下d，方块向右移动一格，值向右传递，类似于方块的下落的结构
while(_kbhit())
{
int i=_getch()
swtich(i)
{
case w:wplay();
}
参数：void
返回值：void
*/

/*
负责人：小朱
刷新所有游戏数据，回到游戏初始状态
在重新开始游戏和开始游戏时调用
参数：void
返回值；void
*/
void init();

/*
（难点） 
（设置界面对应的flag的值为5）
负责人：陆叁
 设置界面接受键盘信息，依此可以调控游戏的音乐和音量以及初始的游戏方块掉落速度
 w/s切换功能模块
 a/d切换数据
 游戏音乐 <鸡你太美>
 游戏音量<    30   >
 游戏难度<    1    >//speed
 （点击左右的框，框内的数据会相应发生变化）
 回到游戏主界面，点击之后改变flag的值跳转至相应的界面
*/
void setview();

// -------------------- view --------------------



int main()
{
    menuview();
    return 0;
}

void fall()
{
    matrix tmp[4];
    for (int i = 0; i < 4; i++)
    {
        tmp[i].y = smallblocks[i].y;
        tmp[i].x = smallblocks[i].x;
        smallblocks[i].y++;
    }
    if (!judge())//judge函数的判断
    {
        if (num == 0)//判断是否失败，即方块是否一次fall函数都无法执行
        {
            //失败画面
            init();
        }
        else {
            for (int i = 0; i < 4; i++)
                smallblocks[i] = tmp[i];
            crash();//同时把这个方块固化
            next();//配置新的方块
        }
    }
    else num++;
    speed = speednormal;//正常速度的保持
}



void crash()//在方块不能自动下落时候实现的固定到map上的作用
{
    for (int i = 0; i < 4; i++)
    {
        map[smallblocks[i].y][smallblocks[i].x] = 1;//打印到map中
    }
}



bool judge()//判断函数的实现
{
    for (int i = 0; i < 4; i++)
        if (smallblocks[i].x < 0 || smallblocks[i].x>CONST_COL - 1 ||
            smallblocks[i].y < 0 || smallblocks[i].y>CONST_ROW - 1 ||
            map[smallblocks[i].y][smallblocks[i].x])
            return false;

    return true;
}



void next()
{
	num = 0;
	int blocks[7][4] = {
		1,3,5,7,
		2,4,5,7,
		3,5,4,6,
		3,5,4,7,
		2,3,5,7,
		3,5,7,6,
		2,3,4,5
	};
	int blockType = 1 + rand() % 7;//方块的随机类型

	//初始化 smallblocks
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[blockType - 1][i];
		smallblocks[i].y = value / 2;
		smallblocks[i].x = value % 2;
	}
}

int getDelay()//新函数：时间间隔的获取
{
    static unsigned long long lastTime = 0;//只有第一次调用才实现
    unsigned long long currentTime = GetTickCount64();//系统时钟

    if (lastTime == 0)
    {
        lastTime = currentTime;
        return 0;
    }
    else {
        int ret = currentTime - lastTime;
        lastTime = currentTime;
        return ret;
    }
}

void playoperate()
{
    char ch;
    bool rotateFlag = false;
    int dx = 0;
    if (_kbhit())
    {
        ch = _getch();

        switch (ch)
        {
        case 'w':
            rotateFlag = true;
            break;
        case 'a':
            dx = -1;
            break;
        case 'd':
            dx = 1;
            break;
        case 's':
            speed = speedquick;//在fall函数中应修改speed为speednormal
            break;
        }
        if (rotateFlag)
        {
            rotate();
            update = true;
        }
        if (dx != 0)
        {
            moveLeftRight(dx);
            update = true;//实现画面的立即更新
        }
    }
}

void eliminate()
{
    int line = 0;//储存消除的行数
    int getScore[4] = { 1000, 2400, 3600, 5200 };
    int k = CONST_ROW - 1;
    for (int i = CONST_ROW - 1; i >= 0; i--)
    {
        bool ok = true;
        for (int j = CONST_COL - 1; j >= 0; j--)
        {
            if (!map[i][j])ok = false;//判断一行是否充满
            map[k][j] = map[i][j];//一边扫描一边储存
        }
        if (!ok)
            k--;//不是满行接着复制下一行
        else
        {
            line++;
        }
    }
    if (line > 0)
    {
        score += getScore[line - 1];//计算得分
        update = true;
    }

    if (score >= setscore)
    {
        winview();//成功界面
    }
};

bool decide(int i, int j)
{
    int end = 0;
    if (map[i + 1][j] == 0) {
        end = 1;
    }
    return end;
};

void drop(int i, int j)
{
    for (; map[i + 1][j] == 0 && map[i][j] != 4; ) {

        int a = map[i + 1][j];
        map[i + 1][j] = map[i][j];
        map[i][j] = a;
        i++;
    }
    eliminate();
};

void died()//死亡界面flag==3,直接判断静止方块的1的位置
{
    for (int i = 0; i < 11; i++) {
        if (map[4][i] == 1) {//如果顶部边界有静止的小方块，则游戏结束
            flag = 3;//赋值给flag，用于页面跳转
            page();
        }
    }
};


void win()
{
    if (score >= setscore) {
        flag = 4;
        page();
    }
};

void page()
{
    while (1)
        {
            switch (flag) {//根据flag值，调用不同界面
            case 1:
                menuview();
                break;
            case 2:
                gameview();
                break;
            case 3:
                diedview();
                break;
            case 4:
                winview();
                break;
            case 5:
                setview();
                break;
            case 6:
                gameexplain();
                break;
            }
        }
};

void rotate()//新函数：实现方块的旋转
{
    matrix tmp[4], p = smallblocks[1];
    for (int i = 0; i < 4; i++)
    {
        matrix temp = smallblocks[i];
        tmp[i].y = smallblocks[i].y;
        tmp[i].x = smallblocks[i].x;
        smallblocks[i].y = p.y + temp.x - p.x;
        smallblocks[i].x = p.x - temp.y + p.y;
    }
    if (!judge())//judge函数的判断                      
        for (int i = 0; i < 4; i++)
            smallblocks[i] = tmp[i];
}

void moveLeftRight(int offset)//新函数：实现方块的左右移动
{
    matrix tmp[4];
    for (int i = 0; i < 4; i++)
    {
        tmp[i].y = smallblocks[i].y;
        tmp[i].x = smallblocks[i].x;
        smallblocks[i].x += offset;
    }

    if (!judge())//judge函数的判断
        for (int i = 0; i < 4; i++)
            smallblocks[i] = tmp[i];
}

void gamefuction()
{
    //在此处完成代码
    int i = _kbhit();
    if (i == '1')
    {
        int a = 1;
        while (a)
        {
            if (getchar() == 1) break;
        }
    }
    if (i == '2')
    {
        init();
        gameview();
    }
    if (i == '3')
    {
        menuview();
    }
}

void setPrintColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void clear(int x, int y, int w, int h)
{
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; j++) putchar(' ');
    }
}

void menuview()
{
    system("cls");
    int userChoose = 0;
    while (1) {
        // ----------------- 打印界面 -----------------
        gotoXY(35, 18);
        printf("按回车表示确定,s或S表示向下移w或W表示向上移");
        gotoXY(53, 3);
        printf("俄罗斯方块");
        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(54, 6);
        printf("开始游戏");
        if (userChoose == 0) setPrintColor(0x0f);
        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(54, 9);
        printf("游戏说明");
        if (userChoose == 1) setPrintColor(0x0f);
        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(54, 12);
        printf("游戏设置");
        if (userChoose == 2) setPrintColor(0x0f);
        if (userChoose == 3) setPrintColor(0x6f);
        gotoXY(54, 15);
        printf("退出游戏");
        if (userChoose == 3) setPrintColor(0x0f);
        // ---------------- 接收用户输入 --------------
        char input = _getch();
        // -------------判断是方向上下还是回车------------
        switch (input) {
        case 'w':
            userChoose -= 1;
            if (userChoose == -1) userChoose = 3;
            break;
        case 's':
            userChoose = (userChoose + 1) % 4;
            break;
        case '\r':
            clear(3, 2, 80, 20);
            switch (userChoose) {
            case 0:
                gameview();
                break;
            case 1:
                gameexplain();
                break;
            case 2:
                setview();
                break;
            case 3:
                exit(0);
                break;
            }
            clear(3, 2, 36, 20);
            break;
        }
    }
};

void gameexplain()
{
    //在此处完成代码
}

void gotoXY(int x, int y)//新函数：更新光标
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void updateWindow()//原文件的mouse函数
{
    system("cls");

    gotoXY(32, 2);
    cout << "score:" << score;
    for (int i = 0; i < CONST_ROW + 1; i++)
    {
        gotoXY(9, i);
        putchar('|');
        gotoXY(10 + CONST_COL, i);
        putchar('|');
    }
    for (int i = 0; i < CONST_COL; i++)
    {
        gotoXY(i + 10, CONST_ROW);
        putchar('_');
    }
    for (int i = 0; i < CONST_ROW; i++)
    {
        for (int j = 0; j < CONST_COL; j++)
        {
            if (map[i][j] == 0)continue;

            gotoXY(j + 10, i);
            SetColor(0x0c);
            cout << "#";
        }
    }
    for (int i = 0; i < 4; i++)
    {
        gotoXY(smallblocks[i].x + 10, smallblocks[i].y);
        SetColor(0x09);
        cout << "#";
    }
}

void gameview()
{
    init();
    next();
    srand((unsigned)time(NULL));//配置随机种子
    int timer = 0;
    while (1)
    {
        playoperate();//接受用户输入
        gamefuction();
        timer += getDelay();//时间变化的表示
        if (timer > speed)
        {
            timer = 0;
            fall();//自动下落
            eliminate();//消除
            died();
            win();
            update = true;
        }
        if (update)
        {
            update = false;
            updateWindow();//更新游戏画面+
        }
    }
};

void keyEvent() {
    int ch;
    while (1) {
        if (_kbhit()) {
            ch = _getch();
        }
    }
}

void gametime() { //记录游戏开始时间
    time_t startTime = time(nullptr);

    while (true) {
        time_t currentTime = time(nullptr); //获取当前时间
        int elapsedTime = difftime(currentTime, startTime); //计算已经过去的时间
        //显示实时游戏时间和速度
        cout << "Game Time: " << elapsedTime << " seconds" << "," << "GameSpeed: " << gameSpeed << endl;

        if (elapsedTime >= 120 && elapsedTime % 120 == 0) {
            gameSpeed++;
            cout << "GameSpeed increased to: " << gameSpeed << endl;
        }
        Sleep(1);     //每一秒更新一次
    }
    //在此处完成代码
};

void diedview()
{
    system("cls");
    int i = 0;
    // 输入w、s
    cout << "\t*******************************\t" << endl;
    cout << "\t\tGame Defeated" << endl;
    cout << "\t*******************************\t" << endl;
    cout << "\t    很遗憾，您的挑战失败了！" << endl;
    cout << "\t*******************************\t" << endl;
    cout << "\t1.重新开始游戏" << endl;
    cout << "\t2.返回主界面" << endl;
    cout << "\t3.退出游戏" << endl;
    cout << "\t请输入1、2、3进行下一步操作：";
    cin >> i;
    switch (i) {
    case 1:
        init(); gameview();//重新开始：再次初始化游戏数据，重新打印游戏界面
        break;
    case 2:
        menuview();//调用菜单栏
        break;
    case 3:
        exit(0);//退出游戏
        break;
    }
};

void winview()
{
    system("cls");
    int i = 0;
    // 输入w、s
    cout << "\t*******************************\t" << endl;
    cout << "\t\tGame Win" << endl;
    cout << "\t*******************************\t" << endl;
    cout << "\t    恭喜您，成功获得游戏胜利！" << endl;
    cout << "\t*******************************\t" << endl;
    cout << "\t1.重新开始游戏" << endl;
    cout << "\t2.返回主界面" << endl;
    cout << "\t3.退出游戏" << endl;
    cout << "\t请输入1、2、3进行下一步操作：";
    cin >> i;
    switch (i) {
    case 1:
        init(); 
        gameview();//重新开始：再次初始化游戏数据，重新打印游戏界面
        break;
    case 2:
        menuview();//调用菜单栏
        break;
    case 3:
        exit(0);//退出游戏
        break;
    }
};

void init()
{
    //重置所有全局变量，恢复至初始状态
    score = 0;
    gameSpeed = 1;
    memset(map, 0, sizeof(map));
    system("cls");
}

void setview(){};
