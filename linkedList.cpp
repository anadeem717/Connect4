#include "linkedList.h"
#include <iostream>

using namespace std;

/*
 * @brief: Default constructor for Linked List
 * 
 * @param: none
 * 
 * @return: none 
 * 
 */
BoardNode::BoardNode() {
    for (int i = 0; i < 42; i++){
        board[i] = '-';
    }
    
    link = nullptr; 
}

/*
 * @brief: Adds a new board to the FRONT of linked list
 * 
 * @param: the board array and the current head of linked list
 * 
 * @return: none, just adds a board to front of linked list
 * 
 */
void BoardNode::addBoard(char newBoard[], BoardNode*& head) {
    BoardNode* newNode = new BoardNode();     // new node to be the head of list
    for (int i = 0; i < 42; i++){
        newNode->board[i] = newBoard[i];
    }
    newNode->link = head;           // newNode link should point to head
    head = newNode;                 // now head should be the newest node
}

/*
 * @brief: Function that displays the board with the player moves
 * 
 * @param: board: The 1D board array
 * 
 * @return: None, prints the board in console
 * 
 */
void BoardNode::displayBoard(char board[]) {
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
 * @brief: Function that displays all board moves for the game
 * 
 * @param: A pointer to a board node
 * 
 * @return: None, prints the board moves
 * 
 */
void BoardNode::printBoards(BoardNode* boardNode) {
    // base case: if the current node is nullptr
    if (boardNode == nullptr) {
        return;
    }

    // Recursive call to the next node
    printBoards(boardNode->link);

    // to print the boards recursively backwards since we are adding boards to the front
    displayBoard(boardNode->board);
}


/*
 * @brief: Undos the last move in the game
 * 
 * @param: board: The 1D board array and current head of list
 * 
 * @return: bool: true if move is undone, false if not possible to undo
 * 
 */
bool BoardNode::undoMove(char board[], BoardNode*& head) {
    if (head == nullptr || head->link == nullptr) {
        return false; // can't undo if no moves made
    }

    BoardNode* tempNode = head;    // set a temp node to the head
    head = head->link;             // the next move should be the head now

    for (int i = 0; i < 42; i++) {
        board[i] = head->board[i];
    }

    delete tempNode;              // delete the temp head node. 
    return true;                  // return true if move undone
}
