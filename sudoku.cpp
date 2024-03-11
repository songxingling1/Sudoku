#include "sudoku.h"
#include <vector>
#include <QDebug>
using namespace std;

Sudoku::Sudoku ():checkerboard(10,vector<int>(10,-1)),p(10,vector<int>(10,0)),row(10,vector<int>(10,0)),
      column(10,vector<int>(10,0)),gong(10,vector<int>(10,0)){}
void Sudoku::change(int x,int y,int num) {
    checkerboard[x][y] = num;
    p[x][y] = 0;
}
void Sudoku::erase(int x, int y) {
    change(x,y,-1);
}
CheckStatus Sudoku::check() {
    vector<int> tmp;
    for(int i = 1;i <= 9;i++) {
        tmp.clear();
        tmp.resize(10,-1);
        for(int j = 1;j <= 9;j++) {
            qDebug() << i << " " << j;
            if(checkerboard[i][j] == -1) return CheckStatus::INCOMPLETE;
            if(tmp[checkerboard[i][j]] != -1) return CheckStatus::NOT_SATISFIABLE;
            tmp[checkerboard[i][j]] = 1;
        }
    }
    for(int j = 1;j <= 9;j++) {
        tmp.clear();
        tmp.resize(10,-1);
        for(int i = 1;i <= 9;i++) {
            qDebug() << i << " " << j;
            if(tmp[checkerboard[i][j]] != -1) return CheckStatus::NOT_SATISFIABLE;
            tmp[checkerboard[i][j]] = 1;
        }
    }
    for(int k = 0;k < 9;k++) {
        tmp.clear();
        tmp.resize(10,-1);
        for(int i = 1 + dx[k];i <= 3 + dx[k];i++) {
            for(int j = 1 + dy[k];j <= 3 + dy[k];j++) {
                qDebug() << i << " " << j;
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
void Sudoku::ChangeStatus() {
    row.clear();
    row.resize(10,vector<int>(10,0));
    column.clear();
    column.resize(10,vector<int>(10,0));
    gong.clear();
    gong.resize(10,vector<int>(10,0));
}
bool Sudoku::getAnswer(int x,int y) {
    int newx,newy;
    newx = x + 1;
    newy = y;
    if(newx > 9) {
        newy++;
        newx = 1;
    }
    if(p[x][y]) {
        return getAnswer(newx,newy);
    }
    bool isOk = false;
    for(int i = 1;i <= 9;i++) {
        if(!row[x][i] && !column[y][i] && !gong[dgong[x][y]][i]) {
            checkerboard[x][y] = i;
            row[x][i] = 1;
            column[y][i] = 1;
            gong[dgong[x][y]][i] = 1;
            isOk = isOk || getAnswer(newx,newy);
            checkerboard[x][y] = -1;
            row[x][i] = 0;
            column[y][i] = 0;
            gong[dgong[x][y]][i] = 0;
        }
    }
    return isOk;
}
