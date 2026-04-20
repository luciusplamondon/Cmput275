#include <iostream>
#include <string>
using namespace std;

struct Grid{
    char **grid;
    int row;
    int col;
    int cap;
    
    Grid() : grid(nullptr), row(0), col(0), cap(4){ //base
        grid = new char*[cap];
    }
    ~Grid(){ //destructor
        for (int i = 0; i < row; ++i){
            delete[] grid[i];
        }
        delete[] grid;
    }
    void grow() { //
        cap *= 2; 
        char** newGrid = new char*[cap];
        for (int i = 0; i < row; i++) {
            newGrid[i] = grid[i];
            }
        delete[] grid; 
        grid = newGrid;
        }
    void addRow(const string& line) {
        if (row == cap) {
            grow();
        }
        col = line.length();
        grid[row] = new char[col];
        for (int j = 0; j < col; ++j) {
            grid[row][j] = line[j];
        }
        row++;
    }
    int countNeighbors(int r, int c) {
        int count = 0;
        for (int i=-1; i <= 1; ++i){
            for (int j = -1; j <= 1; ++j){
                if (i == 0 && j == 0) continue;
                int nrow = r + i;
                int ncol = c + j;
                if (nrow >= 0 && nrow < row && ncol >= 0 && ncol < col) {
                    if (grid[nrow][ncol] == 'O') count++;
                }
            }
        }
        return count;
    }
    void step() {
    char** next = new char*[row]; 
    for (int i = 0; i < row; ++i) {
        next[i] = new char[col];
    }
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            int neighbors = countNeighbors(r, c);

            if (grid[r][c] == 'O') {
                // live cells
                if (neighbors < 2 || neighbors > 3) next[r][c] = '.';
                else next[r][c] = 'O';
            } else {
                // dead cells
                if (neighbors == 3) next[r][c] = 'O';
                else next[r][c] = '.';
            }
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            grid[i][j] = next[i][j];
        }
        delete[] next[i];
    }
    delete[] next;
}
    void print() {
        if (row == 0 || col == 0) return;
        for (int j = 0; j < col; ++j) cout << '|';
        cout << endl;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                cout << grid[i][j];
            }
            cout << endl;
        }
        for (int j = 0; j < col; ++j) cout << '|';
        cout << endl;
    }
};

int main(int argc, char const *argv[]){
    Grid game;
    string first;
    if (getline(cin, first) && first != "x") {
        game.col = first.length(); // This is the # of char in the first line (check the sample)
        game.addRow(first);
    }

    char ch;
    string buffer = "";
    while (cin >> ch && ch != 'x') { //since we have a set col, we simply jsut put everycharacter in
        buffer += ch;
        if (buffer.length() == (size_t)game.col) { //when buffer is the size of the colmum, insert it to the new col
            game.addRow(buffer);
            buffer = "";
        }
    }
    if (buffer != ""){
        game.addRow(buffer);
    }
    char cmd;
    while (cin >> cmd) {
        if (cmd == 'p') game.print();
        else if (cmd == 's') game.step();
    }

    return 0;

}