#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>
using namespace std;
const int dx[9] = {0,3,6,0,3,6,0,3,6};
const int dy[9] = {0,0,0,3,3,3,6,6,6};
const int dgong[10][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,2,2,2,3,3,3},
    {0,1,1,1,2,2,2,3,3,3},
    {0,1,1,1,2,2,2,3,3,3},
    {0,4,4,4,5,5,5,6,6,6},
    {0,4,4,4,5,5,5,6,6,6},
    {0,4,4,4,5,5,5,6,6,6},
    {0,7,7,7,8,8,8,9,9,9},
    {0,7,7,7,8,8,8,9,9,9},
    {0,7,7,7,8,8,8,9,9,9}
};
enum class CheckStatus {
    SUCCESE,INCOMPLETE,NOT_SATISFIABLE
};

class Sudoku {
private:
    vector<vector<int>> checkerboard;
    bool startOk;

public:
    vector<vector<int>> row;
    vector<vector<int>> column;
    vector<vector<int>> gong;
    vector<vector<int>> p;
    Sudoku ();
    void erase(int x, int y);
    void change(int x,int y,int num);
    int getNum(int x,int y);
    CheckStatus check();
    bool getAnswer(int x = 1,int y = 1);
    void ChangeStatus();
};

#endif          // SUDOKU_H
