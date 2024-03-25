#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>
using namespace std;
const int dx[9] = { 0, 3, 6, 0, 3, 6, 0, 3, 6 };          // 每一行所处的宫的左上角的行
const int dy[9] = { 0, 0, 0, 3, 3, 3, 6, 6, 6 };          // 每一列所处的宫的左上角的列
const int dgong[10][10] = {          //每一位属于哪个宫
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 2, 2, 2, 3, 3, 3 },
    { 0, 1, 1, 1, 2, 2, 2, 3, 3, 3 },
    { 0, 1, 1, 1, 2, 2, 2, 3, 3, 3 },
    { 0, 4, 4, 4, 5, 5, 5, 6, 6, 6 },
    { 0, 4, 4, 4, 5, 5, 5, 6, 6, 6 },
    { 0, 4, 4, 4, 5, 5, 5, 6, 6, 6 },
    { 0, 7, 7, 7, 8, 8, 8, 9, 9, 9 },
    { 0, 7, 7, 7, 8, 8, 8, 9, 9, 9 },
    { 0, 7, 7, 7, 8, 8, 8, 9, 9, 9 }
};
// 检查结果
enum class CheckStatus {
    SUCCESE,
    INCOMPLETE,
    NOT_SATISFIABLE
};
// 数独棋盘类
class Sudoku {
private:
    vector<vector<int>> checkerboard;          //棋盘
    bool startOk;          //题目是否有错误i

public:
    vector<vector<int>> row;          //行占用
    vector<vector<int>> column;          //列占用
    vector<vector<int>> gong;          //宫占用
    vector<vector<int>> p;          //修改权限
    Sudoku();
    void erase(int x, int y);          //删除某一位
    void change(int x, int y, int num);          //改变某一位
    int getNum(int x, int y);          //获取某一位上的数字
    CheckStatus check();          //检查是否正确
    bool getAnswer(int x = 1, int y = 1);          //揭秘
    void ChangeStatus();          //准备揭秘
};

#endif          // SUDOKU_H
