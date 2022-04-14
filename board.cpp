#include <iostream>
#include <string>
#include "board.h"

Board::Board()
{
    winnerXorO = '_';
    // initialize the rows
    for (int iLoopCreateRows = 0; iLoopCreateRows < numberOfRows; iLoopCreateRows++) {
        // declare a vector of chars
        vector<int> rowOfInts;

        // initalize each of the columns
        for (int iLoopRow = 0; iLoopRow < numberOfIntsInRow; iLoopRow++) {
            // put 7 chars into the vector
            rowOfInts.push_back(0); //placeholder value
        };
        eachRowOfSpaces.push_back(rowOfInts);
    };
}

bool Board::doMove(int columnNumber, char playerXorO)
{
    bool returnDoMove = false;
    int iPlayer = 0;
    if (playerXorO == 'X') {
        iPlayer = 1; 
    }
    else {
        if (playerXorO == 'O') {
            iPlayer = 2;
        }
        else {
            return returnDoMove;
        };
    };

    // start bottom-most square
    // if square is open, put in X or O
    // if go through whole column and no X or O placed, return false
    if ((columnNumber >= 0) && (columnNumber < int(eachRowOfSpaces[0].size()))) {
        for (int iLoopThroughRows = (int(eachRowOfSpaces.size()) - 1); iLoopThroughRows > - 1; iLoopThroughRows--) {
            if (eachRowOfSpaces[iLoopThroughRows][columnNumber] == 0) {
                eachRowOfSpaces[iLoopThroughRows][columnNumber] = iPlayer;
                returnDoMove = true;
                break;
            };
        };
    };
    winnerXorO = checkWin();
    return returnDoMove;
}
string Board::displayBoard() {
    string returnBoard = "\n";
    for (int iLoopRows = 0; iLoopRows < int(eachRowOfSpaces.size()); iLoopRows++) {
        for (int iLoopWithinThisRow = 0; iLoopWithinThisRow < int(eachRowOfSpaces[0].size()); iLoopWithinThisRow++) {
            if (eachRowOfSpaces[iLoopRows][iLoopWithinThisRow] == 0) {
                returnBoard += "_";
            }
            else {
                if (eachRowOfSpaces[iLoopRows][iLoopWithinThisRow] == 1) {
                    returnBoard += "X";
                }
                else {
                    if (eachRowOfSpaces[iLoopRows][iLoopWithinThisRow] == 2) {
                        returnBoard += "O";
                    }
                    else {
                        returnBoard += "E";
                    }
                }
            }
            returnBoard += " ";
        };
        returnBoard += "\n";
    };
    return returnBoard;
};


char Board::checkWin()
{
    bool winIsPossible = false; //set this to true if we find any 4 consecutive spaces open
    char returnGetWinner = '_';
    // check rows for victory
    if (returnGetWinner == '_') {
        //use stl for loop mechanism to go through each row
        for (vector<int> thisRow : eachRowOfSpaces) {
            int countRowOpen = 0;
            int countX = 0;
            int countO = 0;
            //use stl for loop mechanism to go through each element in this row
            for (int thisRowElement : thisRow) {
                //at each row, see if we can get 4 in a row of X(1) or O(2)
                //if so, set that player as the winner
                switch (thisRowElement) {
                case 1:
                    countX++;
                    countO = 0;
                    countRowOpen = 0;
                    break;
                case 2:
                    countO++;
                    countX = 0;
                    countRowOpen = 0;
                    break;
                default:
                    countRowOpen++;
                    countX = 0;
                    countO = 0;
                    break;
                };
                if (countX > 3) {
                    returnGetWinner = 'X';
                    break;
                };
                if (countO > 3) {
                    returnGetWinner = 'O';
                    break; 
                };
                if ((returnGetWinner == '_')&&(countRowOpen > 3)) {
                    winIsPossible = true; //we found 4 consecutive spaces open
                    break;
                };
            };
        };
    };
    //check columns for victory
    if (returnGetWinner == '_') {
        //going by the column index, look at each element in the row
        for (int iLoopCols = 0; iLoopCols < (int(eachRowOfSpaces[0].size()) - 1); iLoopCols++) {
            int countColOpen = 0;
            int countX = 0;
            int countO = 0;
            //using the stl for loop mechanism go to the one column we are currently examining 
            //and see if we can find 4 in a row of X(1) or O(2)
            for (vector<int> thisRow : eachRowOfSpaces) {
                int thisColSpace = thisRow[iLoopCols];
                switch (thisColSpace) {
                case 1:
                    countX++;
                    countO = 0;
                    countColOpen = 0;
                    break;
                case 2:
                    countO++;
                    countX = 0;
                    countColOpen = 0;
                    break;
                default:
                    countColOpen++;
                    countX = 0;
                    countO = 0;
                    break;
                };
                if (countX > 3) {
                    returnGetWinner = 'X';
                    break;
                };
                if (countO > 3) {
                    returnGetWinner = 'O';
                    break;
                };
                if ((returnGetWinner == '_') && (countColOpen > 3)) {
                    winIsPossible = true; //we found 4 consecutive spaces open
                    break;
                };
            };
        };
    };
    //check left-to-right diagonal-down for victory
    if (returnGetWinner == '_') {
        int indexOfThisRow = 0;
        for (vector<int> thisRow : eachRowOfSpaces) {
            int indexOfThisColumn = 0; // starting with (0,0)
            for (int w : thisRow) {
                //starting at uppermost left (0,0) of the grid, 
                //if it is possible, examine the next three diagonal-right squares 
                //(e.g. from 0,0 look at 1,1|2,2|3,3)
                //and note if they all match / are equal
                int x = 0;
                if ((indexOfThisRow + 3) < int(eachRowOfSpaces.size())) {
                    if ((indexOfThisColumn + 3) < int(eachRowOfSpaces[0].size())) {
                        x = eachRowOfSpaces[indexOfThisRow + 1][indexOfThisColumn + 1];
                        if (w == x) {
                            int y = 0;
                            y = eachRowOfSpaces[indexOfThisRow + 2][indexOfThisColumn + 2];
                            if (w == y) {
                                int z = 0;
                                z = eachRowOfSpaces[indexOfThisRow + 3][indexOfThisColumn + 3];
                                if (w == z) {
                                    if (w == 1) {               //all 4 in diagonal are X
                                        returnGetWinner = 'X';
                                        break;
                                    };
                                    if (w == 2) {               //all 4 in diagonal are O
                                        returnGetWinner = 'O';
                                        break;
                                    };
                                    if (w == 0) {
                                        winIsPossible = true; //we found 4 consecutive spaces open
                                    };
                                };
                            };
                        };
                    };
                };
                indexOfThisColumn++;
            };
            if (returnGetWinner != '_')
                break;
            indexOfThisRow++;
        };
    };
    //check right-to-left diagonal-down for victory
    if (returnGetWinner == '_') {
        int indexOfThisRow = 0;
        for (vector<int> thisRow : eachRowOfSpaces) {
            int indexOfThisColumn = 0;
            for (int w : thisRow) {
                //starting at uppermost left (0,0) of the grid, 
                //if it is possible, examine the next three diagonal-left squares 
                //(e.g. from 0,3 look at 1,2|2,1|3,0)
                //and note if they all match / are equal
                int x = 0;
                if ((indexOfThisRow + 3) < int(eachRowOfSpaces.size())) {
                    if ((indexOfThisColumn - 3) > -1) {
                        x = eachRowOfSpaces[indexOfThisRow + 1][indexOfThisColumn - 1];
                        if (w == x) {
                            int y = 0;
                            y = eachRowOfSpaces[indexOfThisRow + 2][indexOfThisColumn - 2];
                            if (w == y) {
                                int z = 0;
                                z = eachRowOfSpaces[indexOfThisRow + 3][indexOfThisColumn - 3];
                                if (w == z) {
                                    if (w == 1) {             //all 4 in diagonal are X
                                        returnGetWinner = 'X';
                                        break;
                                    };
                                    if (w == 2) {             //all 4 in diagonal are O
                                        returnGetWinner = 'O';
                                        break;
                                    };
                                    if (w == 0) {
                                        winIsPossible = true; //we found 4 consecutive spaces open
                                    };
                                };

                            };
                        };
                    };
                };
                indexOfThisColumn++;
            };
            if (returnGetWinner != '_')
                break;
            indexOfThisRow++;
        };
    };
    //if we get to the end of this method without a possible way to win
    //and neither player having 4 in a row, label it a tie
    if ((winIsPossible == false) && (returnGetWinner == '_'))
        returnGetWinner = 'T';
    return returnGetWinner;
};