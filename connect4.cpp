// connect4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
#include "board.h"

bool isNumber(std::string inputString) {
    if (inputString.size() == 0) {
        return false;
    };
    for (unsigned iLoopString = 0; iLoopString < inputString.size(); iLoopString++) {
        if ((inputString[iLoopString] >= '0' && inputString[iLoopString] <= '9') == false) {
            return false;
        }
    };
    return true;
};

string getWinTieMessage(Board& anyBoard) {
    string returnMessage = "";
    if (anyBoard.getWinnerXorO() == 'E') {
        returnMessage = "ERROR";
    } else {
        if (anyBoard.getWinnerXorO() == 'T') {
            returnMessage = "NO WINNER. THE GAME IS A TIE.";
        }
        else {
            returnMessage = "**********************\nTHE WINNER IS: ~~ ";
            returnMessage.push_back(anyBoard.getWinnerXorO());
            returnMessage += " ~~\n**********************\n";
        };
    };
    return returnMessage;
};

int main()
{
    bool loopGame = true;
    bool changeTurn = false;
    string playerMove = "";
    cout << "------------------\n";
    cout << "~ CONNECT FOUR ~\n";
    cout << "------------------\n";
    while (loopGame) {
        Board gameBoard = Board();
        char currentPlayer = 'X';
        while (gameBoard.getWinnerXorO() == '_') {
            cout << gameBoard.displayBoard();
            while (!changeTurn) {
                cout << "\nEnter move (0-6) for " << currentPlayer << ": ";
                cin >> playerMove; //column number 0 - ?
                if (isNumber(playerMove)) {
                    changeTurn = gameBoard.doMove(stoi(playerMove), currentPlayer);
                };
                if (changeTurn == false) {
                    cout << "Error. Try again.\n";
                };
            };
            if (currentPlayer == 'X') {
                currentPlayer = 'O';
            }
            else {
                currentPlayer = 'X';
            };
            changeTurn = false;
        }; //while
        cout << "\n\n";
        cout << gameBoard.displayBoard();
        cout << "\n" << getWinTieMessage(gameBoard) << "\n";
        char playAgain;
        cout << "\nPlay again (enter Y or y)?";
        cin >> playAgain;
        if ((playAgain == 'Y') || (playAgain == 'y')) {
            cout << std::string(100, '\n');
        } else {
            cout << "\n\nThanks for playing. Goodbye!\n\n";
            loopGame = false;
        };
    };
    return(0);
};

void testHarness() {
    Board rowWin = Board();
    rowWin.doMove(0, 'X');
    rowWin.doMove(0, 'O');
    rowWin.doMove(1, 'X');
    rowWin.doMove(1, 'O');
    rowWin.doMove(2, 'X');
    rowWin.doMove(2, 'O');
    rowWin.doMove(3, 'O');
    rowWin.doMove(3, 'O');
    std::cout << "\n" << rowWin.displayBoard() << "\n" << getWinTieMessage(rowWin) << "\n";

    Board columnWin = Board();
    columnWin.doMove(0, 'X');
    columnWin.doMove(1, 'O');
    columnWin.doMove(0, 'X');
    columnWin.doMove(1, 'O');
    columnWin.doMove(0, 'X');
    columnWin.doMove(1, 'O');
    columnWin.doMove(1, 'O');
    std::cout << "\n" << columnWin.displayBoard() << "\n" << getWinTieMessage(columnWin) << "\n";

    Board diagLtoR = Board();
    diagLtoR.doMove(0, 'X');
    diagLtoR.doMove(0, '0');
    diagLtoR.doMove(0, 'X');
    diagLtoR.doMove(0, 'O');
    diagLtoR.doMove(0, 'X');
    diagLtoR.doMove(1, 'O');
    diagLtoR.doMove(1, 'X');
    diagLtoR.doMove(1, 'X');
    diagLtoR.doMove(2, 'O');
    diagLtoR.doMove(2, 'X');
    diagLtoR.doMove(3, 'X');
    std::cout << "\n" << diagLtoR.displayBoard() << "\n" << getWinTieMessage(diagLtoR) << "\n";

    Board diagRtoL = Board();
    diagRtoL.doMove(0, 'X');
    diagRtoL.doMove(1, 'O');
    diagRtoL.doMove(1, 'X');
    diagRtoL.doMove(2, 'O');
    diagRtoL.doMove(2, 'O');
    diagRtoL.doMove(2, 'X');
    diagRtoL.doMove(3, 'O');
    diagRtoL.doMove(3, 'O');
    diagRtoL.doMove(3, 'O');
    diagRtoL.doMove(3, 'X');
    std::cout << "\n" << diagRtoL.displayBoard() << "\n" << getWinTieMessage(diagRtoL) << "\n";

    Board tieGame = Board();
    tieGame.doMove(0, 'X');
    tieGame.doMove(0, 'X');
    tieGame.doMove(0, 'O');
    tieGame.doMove(0, 'O');
    tieGame.doMove(0, 'X');
    tieGame.doMove(0, 'X');
    tieGame.doMove(1, 'O');
    tieGame.doMove(1, 'O');
    tieGame.doMove(1, 'X');
    tieGame.doMove(1, 'X');
    tieGame.doMove(1, 'O');
    tieGame.doMove(1, 'O');
    tieGame.doMove(2, 'X');
    tieGame.doMove(2, 'X');
    tieGame.doMove(2, 'O');
    tieGame.doMove(2, 'O');
    tieGame.doMove(2, 'X');
    tieGame.doMove(2, 'X');
    tieGame.doMove(3, 'O');
    tieGame.doMove(3, 'O');
    tieGame.doMove(3, 'X');
    tieGame.doMove(3, 'X');
    tieGame.doMove(3, 'O');
    tieGame.doMove(3, 'O');
    tieGame.doMove(4, 'X');
    tieGame.doMove(4, 'X');
    tieGame.doMove(4, 'O');
    tieGame.doMove(4, 'O');
    tieGame.doMove(4, 'X');
    tieGame.doMove(4, 'X');
    tieGame.doMove(5, 'O');
    tieGame.doMove(5, 'O');
    tieGame.doMove(5, 'X');
    tieGame.doMove(5, 'X');
    tieGame.doMove(5, 'O');
    tieGame.doMove(5, 'O');
    tieGame.doMove(6, 'X');
    tieGame.doMove(6, 'X');
    tieGame.doMove(6, 'O');
    tieGame.doMove(6, 'O');
    tieGame.doMove(6, 'X');
    std::cout << "\n" << tieGame.displayBoard() << "\n" << getWinTieMessage(tieGame) << "\n";
};