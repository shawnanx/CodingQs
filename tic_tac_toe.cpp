#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Board {
private:
    char data [3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
public:
    Board() {
    }
    
    bool validate(int x, int y) {
        if (x>=3 || x< 0) return false;
        if (y>=3 || y< 0) return false;
        if (data[x][y] == ' ') return true;
        return false;
    }
    
    void update (int x, int y, char piece) {
        data[x][y] = piece;
    }
    
    bool isWinning () {
        for (int i = 0; i < 3; i++) {
            if (data[i][0] == data[i][1] && data[i][0] == data[i][2] && data[i][0]!= ' ') return true;
            if (data[0][i] == data[1][i] && data[0][i] == data[2][i] && data[0][i]!= ' ') return true;
        }
        if (data[0][0] == data[1][1] && data[0][0] == data[2][2] && data[0][0]!= ' ') return true;
        if (data[0][2] == data[1][1] && data[0][2] == data[2][0] && data[0][2]!= ' ') return true;
        return false;
    }
    
    void display () {
        for (int i=0;i<3;i++) {
            cout << "+---+---+---+\n";
            cout << "| ";
            for (int j=0; j<3;j++) {
                cout <<data[i][j] <<" | ";
            }
            cout << "\n";
        }
        cout << "+---+---+---+\n";
    }
};



char getPiece(char turn) {
    if (turn == '1') {
        return 'x';
    }
    return 'o';
}

int main() {
    
    Board newBoard;
    char turn;
    cout << "Play first-hand? \n 1 = first, 2 = second \n";
    cin >> turn;
    
    while (!newBoard.isWinning()) {
        newBoard.display();
        int x = -1;
        int y = -1;
        while (!newBoard.validate(x, y)) {
            cout << "Player" << turn <<"'s turn";
            cin >> x >> y;
            x --;
            y --;
        }
        char piece = getPiece(turn);
        newBoard.update(x, y, piece);
        if (!newBoard.isWinning()) turn = (turn == '2') ? '1' : '2';
    }
    newBoard.display();
    cout << "Player" << turn <<" wins";

    return 0;
}
