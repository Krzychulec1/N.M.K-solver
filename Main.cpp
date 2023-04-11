#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <algorithm>
#include<fstream>


using namespace std;

struct GAME {
        int N = 0;
        int M = 0;
        int K = 0;
        char ActivePlayer = 0;
        char SecondPlayer = 0;
};

int check_win(char** board, GAME game, char player) {
        //horizontal
        int playerTemp = 0;
        if (player == '1')
                playerTemp = 10;
        else
                playerTemp = -10;
        int win = 0;
        for (int i = 0; i < game.N; i++) {
                win = 0;
                for (int j = 0; j < game.M; j++) {
                        if (board[i][j] == player)
                                win++;
                        else
                                win = 0;
                        if (win == game.K)
                                return playerTemp;
                }
        }
        //vertical
        for (int i = 0; i < game.M; i++) {
                win = 0;
                for (int j = 0; j < game.N; j++) {
                        if (board[j][i] == player)
                                win++;
                        else
                                win = 0;
                        if (win == game.K)
                                return playerTemp;
                }
        }
        //diagonal1
        for (int i = 0; i < game.M - game.K + 1; i++) {
                for (int j = 0; j < game.N - game.K + 1; j++) {
                        win = 0;
                        for (int k = 0; k < game.K; k++) {
                                if (board[j + k][i + k] == player)
                                        win++;
                                else
                                        win = 0;
                                if (win == game.K)
                                        return playerTemp;
                        }
                }
        }
        //diagonal2
        for (int i = 0; i < game.N - game.K + 1; i++) {
                for (int j = game.M; j >= game.K - 1; j--) {
                        win = 0;
                        for (int k = 0; k < game.K; k++) {
                                if (board[i + k][j - k] == player)
                                        win++;
                                else
                                        win = 0;
                                if (win == game.K)
                                        return playerTemp;
                        }
                }
        }

        return 0;
}

void Print(char** board, GAME game, int possibleMoves) {
        if (check_win(board, game, game.SecondPlayer) == 0) {
                cout << possibleMoves << endl;
                for (int i = 0; i < game.N; i++) {
                        for (int j = 0; j < game.M; j++) {
                                if (board[i][j] == '0') {
                                        board[i][j] = game.ActivePlayer;
                                        for (int n = 0; n < game.N; n++) {
                                                for (int m = 0; m < game.M; m++) {
                                                        cout << board[n][m] << " ";
                                                }
                                                cout << endl;
                                        }
                                        board[i][j] = '0';
                                }
                        }
                }
        }
        else
                cout << "0" << endl;
}

void GEN_ALL_POS_MOV(GAME game) {
        int possibleMoves = 0;
        cin >> game.N >> game.M >> game.K >> game.ActivePlayer;
        if (game.ActivePlayer == '1')
                game.SecondPlayer = '2';
        else
                game.SecondPlayer = '1';
        char** board = new char* [game.N];
        for (int i = 0; i < game.N; ++i)
                board[i] = new char[game.M];
        for (int i = 0; i < game.N; i++) {
                for (int j = 0; j < game.M; j++) {
                        cin >> board[i][j];
                        if (board[i][j] == '0')
                                possibleMoves++;
                }
        }
        Print(board, game, possibleMoves);
}

void GEN_ALL_POS_MOV_CUT_IF_GAME_OVER(GAME game) {
        int possibleMoves = 0;
        cin >> game.N >> game.M >> game.K >> game.ActivePlayer;
        if (game.ActivePlayer == '1')
                game.SecondPlayer = '2';
        else
                game.SecondPlayer = '1';
        char** board = new char* [game.N];
        for (int i = 0; i < game.N; ++i)
                board[i] = new char[game.M];
        for (int i = 0; i < game.N; i++) {
                for (int j = 0; j < game.M; j++) {
                        cin >> board[i][j];
                        if (board[i][j] == '0')
                                possibleMoves++;
                }
        }
        if (check_win(board, game, game.SecondPlayer) == 0) {
                for (int i = 0; i < game.N; i++) {
                        for (int j = 0; j < game.M; j++) {
                                if (board[i][j] == '0') {
                                        board[i][j] = game.ActivePlayer;
                                        if (check_win(board, game, game.ActivePlayer) != 0) {
                                                cout << "1" << endl;
                                                for (int n = 0; n < game.N; n++) {
                                                        for (int m = 0; m < game.M; m++) {
                                                                cout << board[n][m] << " ";
                                                        }
                                                        cout << endl;
                                                }
                                                return;
                                        }
                                        board[i][j] = '0';
                                }
                        }
                }
                Print(board, game, possibleMoves);
        }
        else
                cout << "0" << endl;

}

bool isMovesLeft(char** board, GAME game)
{
        for (int i = 0; i < game.N; i++)
                for (int j = 0; j < game.M; j++)
                        if (board[i][j] == '0')
                                return true;
        return false;
}

int minimax(char** board, GAME game, bool isMax, int turn,int alpha,int beta)
{
        int score = 0;
        if (turn % 2 == 1)
                score = check_win(board, game, '1');
        else
                score = check_win(board, game, '2');
        if (score == 10)
                return score;
        if (score == -10)
                return score;
        if (isMovesLeft(board, game) == false)
                return 0;
        if (isMax)
        {
                int best = -100;
                int temp = 0;
                for (int i = 0; i < game.N; i++)
                {
                        for (int j = 0; j < game.M; j++)
                        {
                                if (board[i][j] == '0')
                                {
                                        board[i][j] = '1';
                                        temp = minimax(board, game, !isMax, turn + 1, alpha, beta);
                                        board[i][j] = '0';
                                        if (temp > best)
                                                best = temp;
                                        if (best > alpha)
                                                alpha = best;
                                        if (beta <= alpha)
                                                break;
                                }
                        }
                }
                return best;
        }
        else
        {
                int best = 100;
                int temp = 0;
                for (int i = 0; i < game.N; i++)
                {
                        for (int j = 0; j < game.M; j++)
                        {
                                if (board[i][j] == '0')
                                {
                                        board[i][j] = '2';
                                        temp = minimax(board, game, !isMax, turn + 1, alpha, beta);
                                        board[i][j] = '0';
                                        if (temp < best)
                                                best = temp;
                                        if (best < beta)
                                                beta = best;
                                        if (beta <= alpha)
                                                break;
                                }
                        }
                }
                return best;
        }
}

void SOLVE_GAME_STATE(GAME game) {
        cin >> game.N >> game.M >> game.K >> game.ActivePlayer;
        if (game.ActivePlayer == '1')
                game.SecondPlayer = '2';
        else
                game.SecondPlayer = '1';
        char** board = new char* [game.N];
        for (int i = 0; i < game.N; ++i)
                board[i] = new char[game.M];
        for (int i = 0; i < game.N; i++) {
                for (int j = 0; j < game.M; j++) {
                        cin >> board[i][j];
                }
        }
        int winBeg = check_win(board, game, game.SecondPlayer);
        if (winBeg == 0)
        {
                int turn = 0;
                if (game.ActivePlayer == '2')
                        turn = 1;
                int win = 0;
                if (game.ActivePlayer == '1')
                        win = minimax(board, game, true, turn,-1000,1000);
                else
                        win = minimax(board, game, false, turn,-1000,1000);
                if (win == 10)
                        cout << "FIRST_PLAYER_WINS" << endl;
                else if (win == -10)
                        cout << "SECOND_PLAYER_WINS" << endl;
                else
                        cout << "BOTH_PLAYERS_TIE" << endl;
        }
        else if (winBeg == 10)
                cout << "FIRST_PLAYER_WINS" << endl;
        else
                cout << "SECOND_PLAYER_WINS" << endl;
}

int main() {
        char command[100];
        GAME game;
        while (cin >> command) {
                if (strcmp(command, "GEN_ALL_POS_MOV") == 0)
                {
                        GEN_ALL_POS_MOV(game);
                }
                else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
                {
                        GEN_ALL_POS_MOV_CUT_IF_GAME_OVER(game);
                }
                else if (strcmp(command, "SOLVE_GAME_STATE") == 0)
                {
                        SOLVE_GAME_STATE(game);
                }
        }
}
