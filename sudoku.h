#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>
using namespace std;
const int dx[9] = {0,3,6,0,3,6,0,3,6};
const int dy[9] = {0,0,0,3,3,3,6,6,6};
enum class CheckStatus {
    SUCCESE,INCOMPLETE,NOT_SATISFIABLE
};

class Sudoku {
private:
    vector<vector<int>> checkerboard;


public:
    Sudoku ();
    void erase(int x, int y);
    void change(int x,int y,int num);
    int getNum(int x,int y);
    CheckStatus check();
};

#endif          // SUDOKU_H
