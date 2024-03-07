#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>
using namespace std;
enum class CheckStatus {
    SUCCESE,INCOMPLETE,NOT_SATISFIABLE
};

class Sudoku {
private:
    vector<vector<int>> checkerboard;
    const int dx[9] = {0,3,6,0,3,6,0,3,6};
    const int dy[9] = {0,0,0,3,3,3,6,6,6};
public:
    Sudoku ();
    inline void erase(int,int);
    inline void change(int,int,int);
    CheckStatus check();
};

#endif          // SUDOKU_H
