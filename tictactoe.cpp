#include <iostream>

using namespace std;

int n = 3, player = 1, run = 1;
int dt[9] = {0};
int isWin(int a, int b, int c){
    return (a == b) ? ((c == b) ? 1 : 0) : 0;
}

void boardgame(){
    int stage = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int temp = dt[i*n + j];
            if( temp == 0) cout << " " << stage << " ";
            else if(temp == 1) cout << " X ";
            else cout << " O ";
            stage++;
        }
        cout << endl;
    }
    cout << "========" << endl;
}

int endGame(){
    for(int i = 0 ; i < n; i++){
        if(isWin(dt[i * n + 0],dt[i * n + 1],dt[i * n + 2]) && dt[i * n + 0] != 0){
            return dt[i * n + 0];
        }else if(isWin(dt[i],dt[1 * n + i],dt[2 * n + i]) && dt[i] != 0){
            return dt[i];
        }else if(isWin(dt[0],dt[1 * n + 1],dt[2 * n + 2]) && dt[0] != 0){
            return dt[0];
        }else if(isWin(dt[2],dt[1 * n + 1],dt[2 * n + 0]) && dt[2] != 0){
            return dt[2];
        }
    }
    for(int i = 0; i < n*n; i++) if(dt[i]==0) return 0;
    return 3;
}

int minimax(int depth, int isMax){
    int re = endGame();
    if(re != 0){
        return (re == 3) ? 0 : ((re == 1) ? -10 : 10);
    }
    if(isMax){
        int bestScore = -99999999;
        for(int i = 0; i < n*n; i++){
            if(dt[i] != 0) continue;
            dt[i] = 2;
            int score = minimax(depth + 1, 0);
            dt[i] = 0;
            bestScore = max(score, bestScore);
        }
        return bestScore;
    }else{
        int bestScore = 99999999;
        for(int i = 0; i < n*n; i++){
            if(dt[i] != 0) continue;
            dt[i] = 1;
            int score = minimax(depth + 1, 1);
            dt[i] = 0;
            bestScore = min(score, bestScore);
        }
        return bestScore;
    }
}

void setmove(int stage){
    if(player) dt[stage] = 1;

    int bestScore = -99999999;
    int move;
    for(int i = 0; i < n*n; i++){
        if(dt[i] != 0) continue;
        dt[i] = 2;
        int score = minimax(0, 0);
        dt[i] = 0;
        if(score > bestScore){
            bestScore = score;
            move = i;
        }
    }
    dt[move] = 2;
}


void move(){
    if(player){
        boardgame();
        if(endGame()){
            run = 0;
            return;
        }
        int stage;
            cout << "Nhập vi trí muốn đi: ";
            cin >> stage;
        if(stage == 100) run = 0;
        setmove(stage);
    }
}

int main(){
    while(run){
        move();
    }
    cout << "END GAME";

    return 0;
}