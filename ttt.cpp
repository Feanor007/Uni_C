#include <iostream>
using namespace std;
typedef struct input_tag {
    int row = -1;
    int col = -1;
}user_in;
void print_board(char board[3][3], int board_r, int board_c){
    for(int i = 0; i < board_r; i++){
        cout << "-------\n";
        for(int j = 0; j < board_c; j++){
            cout << "|" << board[i][j];
        }
        cout << "|\n";
    }
    cout << "-------" << endl;
}
char check_win(char board[3][3]){
    //vertical
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][0] != ' ' && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }
    //horizontal
    for(int j = 0; j < 3; j++){
        if(board[0][j] == board[1][j] && board[0][j] != ' ' && board[0][j] == board[2][j]){
            return board[0][j];   
        }
    }
    //diagoal
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        return board[2][2];
    }else if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        return board[2][0];
    }else{
        return ' ';
    }
}
int main(){
    int board_r = 3;
    int board_c = 3;
    char board [3][3];
    char flag = ' '; 
    user_in userX;
    user_in userO;
    //Filling up the board with space
    for(int i = 0; i < board_r; i++){
        for(int j = 0; j < board_c; j++){
            board[i][j] = ' ';
        }
    }
    //Print out the board
    print_board(board,board_r,board_c);

    //Ask for users input coordinates
    do{
        cout << "PlayerX: Enter a row number between (0-2)";
        cin >> userX.row;
        cout << "PlayerX: Enter a col number between (0-2): ";
        cin >> userX.col;
        //Check if they entered same coordinates
        if(userO.row == userX.row && userO.col == userX.col){
            cout << "PlayerX: Enter a row number between (0-2)";
            cin >> userX.row;
            cout << "PlayerX: Enter a col number between (0-2): ";
            cin >> userX.col;
        }
        //Check if inputs are out of bound
        if(userX.row < 0 || userX.row > 2){
            cout << "PlayerX: Enter a row number between (0-2)";
            cin >> userX.row;
            cout << "PlayerX: Enter a col number between (0-2): ";
            cin >> userX.col;
        }
        if(userX.col < 0 || userX.col > 2){
            cout << "PlayerX: Enter a row number between (0-2)";
            cin >> userX.row;
            cout << "PlayerX: Enter a col number between (0-2): ";
            cin >> userX.col;
        }
        //Update the board using the coordinates
        board[userX.row][userX.col] = 'x';
        print_board(board,board_r,board_c);
        flag = check_win(board);
        if(flag == 'x'){
            break;
        }

        cout << "PlayerO: Enter a row number between (0-2)";
        cin >> userO.row;
        cout << "PlayerO: Enter a col number between (0-2): ";
        cin >> userO.col;
        //Check if they entered same coordinates
        if(userO.row == userX.row && userO.col == userX.col){
            cout << "PlayerO: Enter a row number between (0-2)";
            cin >> userO.row;
            cout << "PlayerO: Enter a col number between (0-2): ";
            cin >> userO.col;
        }
        //Check if inputs are out of bound
        if(userO.row < 0 || userO.row > 2){
            cout << "PlayerX: Enter a row number between (0-2)";
            cin >> userX.row;
            cout << "PlayerX: Enter a col number between (0-2): ";
            cin >> userX.col;
        }
        if(userO.col < 0 || userO.col > 2){
            cout << "PlayerX: Enter a row number between (0-2)";
            cin >> userX.row;
            cout << "PlayerX: Enter a col number between (0-2): ";
            cin >> userX.col;
        }
        //Update the board using the coordinates
        board[userO.row][userO.col] = 'o';
        print_board(board,board_r,board_c);
        flag = check_win(board);
    }while(flag == ' ');
    //Make sure two users cannot put same coordinate
    //Update printed board from users inputs
    //cout << flag;
    cout << flag << endl;
    switch(flag){
        case ' ':
            cout << "It is a TIE!" << endl;
            break;
        case 'x':
            cout << "Player X WINS!" << endl;
            break;
        case 'o':
            cout << "Player O WINS!" << endl;
            break;
    }
    return 0;
}