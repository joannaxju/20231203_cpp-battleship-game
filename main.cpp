#include "header.h"

int main() 
{ 
    bool computer;                 
    PlayerBoard player1, player2;  
    char player1Enemy[10][10],    
         player2Enemy[10][10];     

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            player1Enemy[i][j] = ' ';
            player2Enemy[i][j] = ' ';
        }
    }

    char choice;
    bool validSelect = false;
    while(!validSelect)
    {
        cout << "Select (a) to play against another player and select (b) to play against a computer: ";
        cin >> choice;
        if(choice == 'a' || choice == 'b')
            validSelect = true;
        else
            cout << "Invalid choice. Please try again.\n" << endl;
    }
    if(choice == 'a')
        computer = false;
    else
        computer = true;
  
    cout << "\n\n\n\n";
        
    initFleet(player1);
    initFleet(player2);
    boardSetup(player1, player2, computer);

    cout << "\n\n\n\n";

    int turn = 1;
    int winner = 0;
    int row = -1, col = -1;
    do
    {
        if(turn == 1)
        {
            winner = playerTurn(player2, player1Enemy, turn);
            displayBoards(player1.board, player1Enemy);
            cout << "\n\n";
            turn = 2;
        }
        else if(turn == 2)
        {
            if(computer)
                winner = computerTurn(player1, player2Enemy, turn, row, col);
            else 
                winner = playerTurn(player1, player2Enemy, turn);
            displayBoards(player2.board, player2Enemy);
            cout << "\n\n";
            turn = 1;
        }
    }
    while(winner == 0);

    if(winner == 1)
        cout << "\n\n\n\nPlayer 1 sunk the fleet!!! Player 1 wins!!!\n";
    else if(winner == 2 && computer)
        cout << "\n\n\n\nPlayer 2 (computer) sunk the fleet!!! Computer wins!!!\n";
    else if(winner == 2 && !computer)
        cout << "\n\n\n\nPlayer 2 sunk the fleet!!! Player 2 wins!!!\n";
  
    return 0;
}