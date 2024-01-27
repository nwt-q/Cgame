#include<iostream>
using namespace std;
#define black "●"
#define white "○"
const int N = 19;


// -------------------- 数据设计 --------------------
/*
    棋盘:
        map[i][j]表示坐标(i,j)的值
        0表示空地
        1表示黑子
        2表示白子
    如: map[3][6] = 1  表示(3,6)的位置是黑子
*/
int map[N][N];

// 表示当前回合数  偶数表示黑棋落子  奇数表示白棋落子
// 如: flag = 20 表示当前是第[20]次落子  由黑方落子
int flag;
// -------------------- 数据设计 --------------------


// -------------------- service --------------------
/*
    功能: 初始化游戏数据
        将棋盘的值初始化为0
        当前回合设为黑棋(flag设为0)
    参数: void
    返回值: void
*/
void init();

/*
    *难点1
    功能: 根据传入的坐标(map对应位置)和flag值 判断落点后是否获胜
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
    返回值:
        0表示没有获胜
        1表示黑子胜利
        2表示白子胜利
*/
int isWin(int x, int y);

/*
    功能: 在指定位置落子
        如果map[x][y]是空地 则修改map[x][y]的值:改为相应颜色(flag对应颜色)
        否则不操作
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
    返回值:
        0表示落子失败 (棋盘已经有子)
        1表示落子成功

*/
int playerMove(int x, int y);
// -------------------- service --------------------



// -------------------- view --------------------
/*
    功能: 展示选项, 玩家可以在这里选择进入游戏, 进入设置或退出游戏
        进入游戏: 调用游戏界面函数gameView();
        进入设置: 敬请期待...
        退出游戏: 调用exit(0);
*/
void menuView();

/*
    功能: 根据map数组 打印游戏棋盘
    参数: void
    返回值: void
*/
void gameView_ShowMap();

/*
    功能: 根据flag的值  打印游戏胜利界面  用户可以按任意键回到主菜单
    参数: void
    返回值: void
*/
void winView();

/*
    *难点2
    负责人: 张三
    功能: 游戏界面整合
        初始化游戏数据(调用函数init())
        while(1){
            打印游戏界面(调用函数gameView_ShowMap())
            接收玩家坐标输入

            落子(调用落子函数playerMove())
                (如果落子失败 重新开始循环)

            判断游戏是否胜利(调用胜利判断函数isWin())
                (如果游戏胜利 调用胜利界面函数 然后结束当前界面)
            切换玩家(修改flag值)
        }
    参数: void
    返回值: void
*/
void gameView();
// -------------------- view --------------------

int main()
{
    system("color F0");
    menuView();
    return 0;
}

void init() {
    memset(map, 0, sizeof(map));
    flag = 1;
    return ;
}
//五子棋怎么判断赢?
//五点一线
//8个方向
int isWin(int row, int cow) {
    //横向
    for (int i = 0; i < row; i++) {
        int count = 0;
        for (int j = 0; j < cow; j++) {
            if (map[i][j] == 1) {
                count++;
                if (count == 5) return true; // 连通5个，当前玩家胜利  
            }
            else {
                count = 0; // 重置计数器  
            }
        }
    }
    for (int i = 0; i < row; i++) {
        int count = 0;
        for (int j = 0; j < cow; j++) {
            if (map[i][j] == 2) {
                count++;
                if (count == 5) return true; // 连通5个，当前玩家胜利  
            }
            else {
                count = 0; // 重置计数器  
            }
        }
    }
    //纵向
    for (int i = 0; i < row; i++) {
        int count = 0;
        for (int j = 0; j < cow; j++) {
            if (map[j][i] == 1) {
                count++;
                if (count == 5) return true; // 连通5个，当前玩家胜利  
            }
            else {
                count = 0; // 重置计数器  
            }
        }
    }
    for (int i = 0; i < row; i++) {
        int count = 0;
        for (int j = 0; j < cow; j++) {
            if (map[j][i] == 2) {
                count++;
                if (count == 5) return true; // 连通5个，当前玩家胜利  
            }
            else {
                count = 0; // 重置计数器  
            }
        }
    }
    //对角线判断
    for (int i = 0; i < row - 4; i++) {
        for (int j = 0; j < cow - 4; j++) {
            if (map[i][j] == map[i + 1][j + 1] && map[i][j] == map[i + 2][j + 2] && map[i][j] == map[i + 3][j + 3]
                && map[i][j] == map[i + 4][j + 4]&&map[i][j]!=0) {
                return true;
            }
        }
    }
    for (int i = 0; i < row - 4; i++) {
        for (int j = 0; j < cow - 4; j++) {
            if (map[i][j] == map[i + 1][j - 1] && map[i][j] == map[i + 2][j - 2] && map[i][j] == map[i + 3][j - 3]
                && map[i][j] == map[i + 4][j - 4])
                return map[i][j];
        }
    }
    return 0;
}



int playerMove(int x, int y) {
    if (map[x][y] == 0) {
        map[x][y] = flag % 2 + 1;
        return 1;
    }
    else {
        return 0;
    }
}

void menuView() {
    while (1) {
        cout << "-------1.进入游戏-------\n"
            << "--------2.进入设置-------\n"
            << "-------0.退出游戏-------\n";
        cout << "输入你的选项:";
        int Case; cin >> Case;
        switch (Case) {
        case 1:
            gameView();
            break;
        case 2:
            cout << "\n敬请期待.··";
            break;
        case 0:
            exit(0);
        }
    }
}


void gameView_ShowMap() {
    system("cls");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (map[i][j] ==1)cout << black;
            else if (map[i][j] == 2)cout << white;
            else {
                if (i == 0 && j == 0)cout << "┌";
                else if (i == 0 && j == N - 1)cout << "┐";
                else if (i == N - 1 && j == 0)cout << "└";
                else if (i == N - 1 && j == N - 1)cout << "┘";
                else if (i == 0)cout << "┬";
                else if (i == N - 1)cout << "┴";
                else if (j == 0)cout << "├";
                else if (j == N - 1)cout << "┤";
                else cout << "┼";
            }
        }
        cout << endl;
    }
}

void winView() {
    if (flag % 2 == 0) {
        cout << "\n恭喜黑子获胜\n";
    }
    else {
        cout<< "\n恭喜白子获胜\n";
    }
    system("puase");
    return ;
}

void gameView() {
    init();
    memset(map, 0, sizeof(map));
    gameView_ShowMap();
    int x, y, k = 0;
    while (1) {
        if (flag % 2 == 0) {
            cout << "输入黑子坐标: ";
            cin >> x >> y;
            k = playerMove(x, y);
        }
        else {
            cout << "输入白子坐标: ";
            cin >> x >> y;
            k = playerMove(x, y);
        }
        system("cls");
        playerMove(x, y);
        gameView_ShowMap();
        if (k == 1) flag++;
        if (k == 0) {
            cout << "\n坐标出错请重新";
        }
        if (isWin(N, N)) {
            gameView_ShowMap();
            winView();
            system("cls");
            return;
        }
    }
}
