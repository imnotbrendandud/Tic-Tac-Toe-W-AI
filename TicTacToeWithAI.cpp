//==========================================================================
// Author: Brendan Czekaj
// Date  : 04-28-2022
// Desc  : Tic-Tac-Toe with an unbeatable AI using the MiniMax Algorithm.
//==========================================================================

#include <iostream>
#include <string>

void displayBoard();
void selection();
void initBoard();
void gameplay();
void clear();
void columnValidityChecks();
void rowValidityChecks();
void optimalMove();
char checkForWinner();
bool checkForAIWin();
bool checkForHumanWin();
bool checkForTie(int);
bool gameIsOver();

bool run = true;
bool gameOver = false;
char board[3][3];
char currentPlayer;
char human = 'O';
char ai = 'X';
bool aiTurn = true;
int whoGoesFirst;
int col;
int row;
int moves = 4;
int bestMove[2];
std::string playAgain;


int minimax(char hBoard[3][3], int depth, bool isMaximizing)
{
    char result = checkForWinner();
    // O = -1, X = +1, T (Tie) = 0
    if (result == 'O')
    {
        int score = -1;
        return score;
    }
    else if (result == 'X')
    {
        int score = 1;
        return score;
    }
    else if (result == 'T')
    {
        int score = 0;
        return score;
    }

    // The maximizer will search for the largest score and return it.
    if (isMaximizing)
    {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (hBoard[i][j] == ' ')
                {
                    hBoard[i][j] = ai;
                    int score = minimax(hBoard, depth + 1, false);
                    hBoard[i][j] = ' ';

                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    // The minimizer will search for the smallest score and return it.
    else
    {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (hBoard[i][j] == ' ')
                {
                    hBoard[i][j] = human;
                    int score = minimax(hBoard, depth + 1, true);
                    hBoard[i][j] = ' ';

                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

int main()
{
    while (run)
    {
        selection();
        initBoard();
        gameplay();
        if (gameIsOver())
        {
            run = false;
        }
        else
        {
            gameOver = false;
            clear();
            aiTurn = true;
        }
    }
}

void initBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void displayBoard()
{
    std::cout << "+===========+" << std::endl;
    std::cout << "|_" << board[0][0] << "_|_" << board[1][0] << "_|_" << board[2][0] << "_|" << std::endl;
    std::cout << "|_" << board[0][1] << "_|_" << board[1][1] << "_|_" << board[2][1] << "_|" << std::endl;
    std::cout << "| " << board[0][2] << " | " << board[1][2] << " | " << board[2][2] << " |" << std::endl;
    std::cout << "+===========+" << std::endl;
}

void selection()
{
    //Selection 1 - AI first, Selection 2 - Human first, Selection 3 - Random
    srand(time(NULL));
    std::cout << "Welcome to Tic-Tac-Toe! Please select who goes first: " << std::endl;
    std::cout << "1 - AI, 2 - Human, 3 - Random" << std::endl;
    std::cin >> whoGoesFirst;

    if (whoGoesFirst == 1)
    {
        aiTurn = true;
        moves = 4;
    }
 
    else if (whoGoesFirst == 2)
    {
        aiTurn = false;
        moves = 5;
    }
    else if (whoGoesFirst == 3)
    {
        // Select a random number from 1 and 2
        int randSelection = rand() % 2 + 1;
        if (randSelection == 1)
        {
            aiTurn = true;
            moves = 4;
        }
        else if (randSelection == 2)
        {
            aiTurn = false;
            moves = 5;
        }
    }
}

void gameplay()
{
    while (!gameOver)
    {
        if (aiTurn)
        {
            displayBoard();
            optimalMove();
        }
        else
        {
            clear();
            displayBoard();
            std::cout << "Human, make your move" << std::endl <<  "Insert row: " << std::endl;

            rowValidityChecks();
            clear();
            displayBoard();
            std::cout << "Human, make your move" << std::endl << "Insert column: " << std::endl;
            std::cout << row << ",";
            columnValidityChecks();

            // Check for open spaces, and place an O where there is an open space.
            if (board[col - 1][row - 1] == ' ')
            {
                board[col - 1][row - 1] = human;
                aiTurn = true;
                clear();
                displayBoard();
                if (checkForHumanWin())
                {
                    gameOver = true;
                }
                moves--;
            }
            else
            {
                std::cout << "That position is already occupied." << std::endl;
            }
        }
    }
}

void columnValidityChecks()
{
    // While the column is not a number, try again
    while (!(std::cin >> col))
    {
        std::cout << "Invalid input, try again please." << std::endl;
        std::cout << "Human, make your move. Insert column: " << std::endl;
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }

    // While the column is greater or less than the range, try again
    while (col > 3 || col < 1)
    {
        std::cout << "Invalid range, try again please." << std::endl;
        std::cout << "Insert column value between 1 and 3: " << std::endl;
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cin >> col;
    }
}

void rowValidityChecks()
{
    // While the row is not a number, try again
    while (!(std::cin >> row))
    {
        std::cout << "Invalid input, try again please." << std::endl;
        std::cout << "Human, make your move. Insert row: " << std::endl;
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }

    // While the row is greater or less than the range, try again
    while (row > 3 || row < 1)
    {
        std::cout << "Invalid range, try again please." << std::endl;
        std::cout << "Insert row value between 1 and 3: " << std::endl;
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cin >> row;
    }
}

void optimalMove()
{
    // Initialize a best score then use minimax to return a score. If the
    // score returned from minimax is greater than current bestScore,
    // update bestScore.
    int bestScore = -1000;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = ai;
                int score = minimax(board, 0, false);
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    // After the minimax algorithm decides at which position the AI should move,
    // it is now the player's turn
    board[bestMove[0]][bestMove[1]] = ai;
    aiTurn = false;

    clear();
    displayBoard();
    if (checkForAIWin() || checkForTie(moves))
    {
        gameOver = true;
    }
}
// This function is solely for assigning a score to the minimax algorithm
char checkForWinner()
{
    char winner = NULL;
    int openSpots = 0;
    // Horizontal and vertical 3 in a row checks
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] != ' ') && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
        {
            winner = board[i][0];
        }

        if ((board[0][i] != ' ') && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
        {
            winner = board[0][i];
        }
    }

    // Diagonal
    if ((board[1][1] != ' ') && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
    {
        winner = board[1][1];
    }

    // Reverse Diagonal
    else if ((board[1][1] != ' ') && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
    {
        winner = board[1][1];
    }

    // We must check how many open spots there are so when all spots are taken,
    // the result is a tie
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                openSpots++;
            }
        }
    }

    // If no winner and no open spots, return T for tie
    if (winner == NULL && openSpots == 0)
    {
        return 'T';
    }
    // Otherwise the function will return an O or an X
    else
    {
        return winner;
    }
}

bool checkForAIWin()
{
    // check for 3 in a row of a column or row
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] != ' ') && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
        {
            std::cout << "The AI bested you!" << std::endl;
            return true;
        }

        if ((board[0][i] != ' ') && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
        {
            std::cout << "The AI bested you!" << std::endl;
            return true;
        }
    }

    // Diagonal
    if ((board[1][1] != ' ') && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
    {
        std::cout << "The AI bested you!" << std::endl;
        return true;
    }

    // Reverse Diagonal
    if ((board[1][1] != ' ') && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
    {
        std::cout << "The AI bested you!" << std::endl;
        return true;
    }

    return false;
}

bool checkForHumanWin()
{
    // check for 3 in a row of a column or row
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] != ' ') && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
        {
            std::cout << "You won! But how?" << std::endl;
            return true;
        }

        if ((board[0][i] != ' ') && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
        {
            std::cout << "You won! But how?" << std::endl;
            return true;
        }
    }

    // Diagonal
    if ((board[1][1] != ' ') && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
    {
        std::cout << "You won! But how?" << std::endl;
        return true;
    }

    // Reverse Diagonal
    if ((board[1][1] != ' ') && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
    {
        std::cout << "You won! But how?" << std::endl;
        return true;
    }

    return false;
}

bool checkForTie(int moves)
{
    if (moves == 0)
    {
        std::cout << "You tied!" << std::endl;
        return true;
    }

    return false;
}

bool gameIsOver()
{
    std::cout << "Would you like to play again? (Y/N): " << std::endl;
    std::cin >> playAgain;

    if (playAgain == "Y" || playAgain == "y") return false;

    else if (playAgain == "N" || playAgain == "n") return true;

    else std::cout << "Please input Y/N" << std::endl;
}

void clear()
{
    system("cls");
}