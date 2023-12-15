
#include <iostream>

class BoardNode {
public:
    char board[42];           // Array to store the board 
    BoardNode* link;          // pointer to linked board

    BoardNode();              // default Constructor

    void addBoard(char newBoard[42], BoardNode*& head); // Add a new board at the FRONT of linked list
    bool undoMove(char board[], BoardNode*& head);      // Undo the last move if possilbe (bool)
    void printBoards(BoardNode* boardNode);             // Print all board moves
    void displayBoard(char board[]);                    // displays a board
};

