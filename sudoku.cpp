#include "sudoku.h"
#include <vector>
using namespace std;

Sudoku::Sudoku ():checkerboard(10,vector<int>(10,-1)) {}
void Sudoku::change(int x,int y,int num) {
    checkerboard[x][y] = num;
}
void Sudoku::erase(int x, int y) {
    change(x,y,-1);
}
CheckStatus Sudoku::check() {
    vector<int> tmp;
    for(int i = 1;i <= 9;i++) {
        tmp.clear();
        tmp.resize(10,-1);
        for(int j = 1;j <= 9;i++) {
            if(checkerboard[i][j] == -1) return CheckStatus::INCOMPLETE;
            if(tmp[checkerboard[i][j]] != -1) return CheckStatus::NOT_SATISFIABLE;
            tmp[checkerboard[i][j]] = 1;
        }
    }
    for(int j = 1;j <= 9;j++) {
        tmp.clear();
        tmp.resize(10,-1);
        for(int i = 1;i <= 9;i++) {
            if(tmp[checkerboard[i][j]] != -1) return CheckStatus::NOT_SATISFIABLE;
            tmp[checkerboard[i][j]] = 1;
        }
    }
    for(int k = 0;k <= 9;k++) {
        tmp.clear();
        tmp.resize(10,-1);
        for(int i = 1 + dx[k];i <= 3 + dx[k];i++) {
            for(int j = 1 + dy[k];j <= 3 + dy[k];i++) {
                if(tmp[checkerboard[i][j]] != -1) return CheckStatus::NOT_SATISFIABLE;
                tmp[checkerboard[i][j]] = 1;
            }
        }
    }
    return CheckStatus::SUCCESE;
}
int Sudoku::getNum(int x,int y) {
    return checkerboard[x][y];
}
