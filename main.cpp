/******************************************************************************
Author: Areesh Nadeem
CS 141 Project 6: Connect 4 With Backtracking
    - This is a program which simulates the game of Connect 4
    - There are 2 players which can play the game and each player takes a turn
        until a player wins or there is a draw
    - Each player can place a piece 'X' for P1 and 'O' for P2 in 1 of 7 columns,
        if the player gets 4 in a row in any direction, they win.  
    - Players can now undo moves in this version which is done using a linked list
Environment: VSCode and ZybooksLab
Date: 12/01/2023
*******************************************************************************/

#include "linkedList.h"
#include <iostream>
#include <string>
using namespace std;

// Functions to be used by program, function comments provided above function defs. 
void displayBoard(char board[]);
void playGame(char board[], int turn, BoardNode*& head);
void insertChoiceOnBoard(char board[], char player, int choice, BoardNode*& head);
bool checkHorizontalWin(char board[], char player);
bool checkVerticalWin(char board[], char player);
bool checkLftRtDiagonalWin(char board[], char player);
bool checkRtLftDiagonalWin(char board[], char player);
bool checkForDraw(char board[]);


int main() 
{
    int turn = 0; // if turn is even -> P1 turn, if odd -> P2 turn

    // 7 x 6 board for connect 4 game
    char board[42] =   
      // 0   1   2   3   4   5   6
       {'-','-','-','-','-','-','-',  // 0-6   
        '-','-','-','-','-','-','-',  // 7-13
        '-','-','-','-','-','-','-',  // 14-20
        '-','-','-','-','-','-','-',  // 21-27
        '-','-','-','-','-','-','-',  // 28-34
        '-','-','-','-','-','-','-',};// 35-41

    BoardNode* boardHead = new BoardNode(); // declaring first node of linkedlist

    cout << "This is the Game Connect 4." << endl;
    cout << "Each player should place an X or an O in the space" << endl;
    cout << "by entering the column you want to place the piece." << endl;
    cout << "The piece will fall until it reaches the bottom or" << endl; 
    cout << "the current pieces in the board. When X or O gets 4 in" << endl; 
    cout << "a row (either horizontally, vertically, or diagonally," << endl; 
    cout << "then that person wins. The user can enter Q (or q) to" << endl; 
    cout << "end the game early." << endl;
    cout << "Let's get started!!! " << endl;

    displayBoard(board);   // displays the current board which is empty initially

    // Calls the main function to play the game (recursive function). 
    // Only needs to be called once because it will continue to recurse 
    // until the game is over (Win or Draw). 
    playGame(board, turn, boardHead);
      
    return 0;
}

/*
 * @brief: Function that displays the board with the player moves
 * 
 * @param: board: The 1D board array
 * 
 * @return: None, prints the board in console
 * 
 */
void displayBoard(char board[]) {
    cout << '\t' << "0 1 2 3 4 5 6" << endl;
  
    for (int i = 0; i < 6; i++) {
        cout << '\t';
        for (int j = 0; j < 7; j++) {
            cout << board[i * 7 + j] << ' ';
        }
        cout << endl;
    }
}

/*
 * @brief: 
 *    - Main recursive function for players to play the game
 *    - Checks to see if user has won the game or draw, if not recurses to next iteration
 * 
 * @param: the 1D board array and the turn number
 * 
 * @return: None, prints the updated board with player moves using displayBoard() func
 * 
 */
void playGame(char board[], int turn, BoardNode*& head) {
    
    string colmnChoice;  // the column choice that the user picks (0-6) or Q/q to quit
    char player;         // either 'X' or 'O' depending on player 1 or 2

    if (turn % 2 == 0) { // if turn is even, its P1 turn
        player = 'X';
        cout << "It is X's turn." << endl;
        cout << "Enter a column to place your piece. ";
        cin >> colmnChoice;
        cout << endl; 
    } 
    else { // if turn is not even, its P2 turn
        player = 'O';
        cout << "It is O's turn." << endl;
        cout << "Enter a column to place your piece. ";
        cin >> colmnChoice;
        cout << endl; 
    }

    // if user wants to quit
    if (colmnChoice == "Q" || colmnChoice == "q") {
        cout << "Ending Game" << endl; 
        exit(1); 
    }

    // if user wants to undo a move
    if (colmnChoice == "U" || colmnChoice == "u") {
        if (head->undoMove(board, head)) {    // if there are moves to undo, do it
            displayBoard(board);
            playGame(board, --turn, head);    // go back to previous turn
        } 
        else {     // if no moves can be undone
            displayBoard(board);
            playGame(board, turn, head);  // keep the turn the same
        }
    return;
    }

    // to print all board moves for the game
    if (colmnChoice == "P" || colmnChoice == "p") {
       head->printBoards(head);
       exit(1);  
    }


    // checks for valid input, colmnChoice can only be an int 0-6
    if (stoi(colmnChoice) > 6) {
        cout << "Please enter a valid column" << endl; 
    }

    // insert players (int) column choice on the board
    insertChoiceOnBoard(board, player, stoi(colmnChoice), head);

    // display the board after each move
    displayBoard(board);

    // base case 1: if a player has won, checks every possibility for a win
    if (checkHorizontalWin(board, player) || checkVerticalWin(board, player) || checkLftRtDiagonalWin(board, player) || checkRtLftDiagonalWin(board, player)) {
        displayBoard(board);
        cout << "Game is Over, Player " << player << " got 4 in a row!!!!" << endl;
        return;
    }
 
    // base case 2: no one wins, board is full and its a draw
    if (checkForDraw(board)) {
        displayBoard(board);
        cout << "Board is Full, It's a Draw!!!" << endl;
        return;
    }

    // recursive call for playGame()
    // continue to play the game until one of the base cases is executed:
    //     -> Player wins or draw 
    playGame(board, ++turn, head); 
}

/*
 * @brief: Inserts the player's character on the board depending on column choice
 * 
 * @param: the 1D board array, player's character, int of column choice
 * 
 * @return: None. Updates the board array with player move
 * 
 */
void insertChoiceOnBoard(char board[], char player, int choice, BoardNode*& head) {
    int row = 5; // max value for row number (0-5) which is 6 rows total

    /*
    - Following loop checks to see if there is a empty spot on the specified column
    - Keeps checking from bottom to top for an empty spot 
    - If there is, place the players character on the board in that spot
    */
    while (row >= 0) {
        if (board[row * 7 + choice] == '-') { 
            board[row * 7 + choice] = player; 
            break;
        }
        row--; 
    }

    // if there are no empty spots on board
    // this means the column is full, ask for user input again for the same player
    if (row == -1) {
        cout << "column chosen is already full" << endl;
        if (player == 'X'){
            playGame(board, 0, head);
        }  
        else {
            playGame(board, 1, head);
        }
    }
    head->addBoard(board, head); // adds the board to the front of linked list
}

/*
 * @brief: Checks the board for any horizontal win conditions
 * 
 * @param: the 1D board array, player character
 * 
 * @return: bool: True if horizontal win found, false if not. 
 * 
 */
bool checkHorizontalWin(char board[], char player) {

    // This loop checks to see if there are 4 spots 
    // with the same character aligned horizontally next to each other. 
    for (int row = 0; row < 6; row++) {
        for (int colmn = 0; colmn < 4; colmn++) {
            if ((board[row * 7 + colmn] == player) && 
            (board[row * 7 + colmn + 1] == player) && 
            (board[row * 7 + colmn + 2] == player) && 
            (board[row * 7 + colmn + 3] == player)) {
                return true; // if win found
            }
        }
    }
    return false; 
}

/*
 * @brief: Checks the board for any vertical win conditions
 * 
 * @param: the 1D board array, player character
 * 
 * @return: bool: True if vertical win found, false if not. 
 * 
 */
bool checkVerticalWin(char board[], char player) {

    // This loop checks to see if there are 4 spots 
    // with the same character aligned vertically next to each other. 
    for (int colmn = 0; colmn < 7; colmn++) {
        for (int row = 0; row < 3; row++) {
            if ((board[row * 7 + colmn] == player) && 
            (board[(row + 1) * 7 + colmn] == player) && 
            (board[(row + 2) * 7 + colmn] == player) && 
            (board[(row + 3) * 7 + colmn] == player)) {
                return true; // if win found
            }
        }
    }
    return false; 
}

/*
 * @brief: Checks the board for any Left-Right Diagonal win conditions
 * 
 * @param: the 1D board array, player character
 * 
 * @return: bool: True if win found, false if not. 
 * 
 */
bool checkLftRtDiagonalWin(char board[], char player) {

    /*
       This loop checks to see if there are 4 spots 
       with the same character aligned diagonally starting
       from the left side of the board.  
    */
    for (int row = 0; row < 3; row++) { // need to check 4 rows
        for (int colmn = 0; colmn < 4; colmn++) {  // only possible L-R diagonal is from colmn 0-3
            if ((board[row * 7 + colmn] == player) && 
            (board[(row + 1) * 7 + colmn + 1] == player) && 
            (board[(row + 2) * 7 + colmn + 2] == player) && 
            (board[(row + 3) * 7 + colmn + 3] == player)) {
                return true; // if win found
            }
        }
    }
    return false; 
}

/*
 * @brief: Checks the board for any Right-Left Diagonal win conditions
 * 
 * @param: the 1D board array, player character
 * 
 * @return: bool: True if win found, false if not. 
 * 
 */
bool checkRtLftDiagonalWin(char board[], char player) {

    /*
       This loop checks to see if there are 4 spots 
       with the same character aligned diagonally starting
       from the right side of the board.  
    */
    for (int row = 0; row < 3; row++) { // check 4 rows
        for (int colmn = 3; colmn < 7; colmn++) {// possible R-L diagonal is starting at colmn 3 to 6
            if ((board[row * 7 + colmn] == player) && 
            (board[(row + 1) * 7 + colmn - 1] == player) &&
            (board[(row + 2) * 7 + colmn - 2] == player) && 
            (board[(row + 3) * 7 + colmn - 3] == player)) {
                return true; // if win found 
            }
        }
    }
    return false; 
}

/*
 * @brief: Checks the board for any empty spots, if no spots are found the board if full 
 * 
 * @param: the 1D board array
 * 
 * @return: bool: True if board is full, false if still empty spots
 * 
 */
bool checkForDraw(char board[]) {
    for (int i = 0; i < 42; i++) {
        if (board[i] == '-') {
            return false;  // if empty slot found
        }
    }
    return true;           // if board full 
}

