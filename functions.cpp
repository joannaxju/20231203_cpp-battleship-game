#include "header.h"

void displayBoards(char board1[][10], char board2[][10]) 
{
    cout << "                     Your Board      ";
    cout << "                                    Enemy Board\n";
    cout << "    1   2   3   4   5   6   7   8   9  10  ";
    cout << SPACE << "    1   2   3   4   5   6   7   8   9  10  \n";
    cout << PARTITION << SPACE << PARTITION << endl;
    for(int r = 0; r < 10; r++)
    {
        char let = r + 65;  
        cout << let << " |";
        for(int c = 0; c < 10; c++)
            cout << " " << board1[r][c] << " |";
        cout << SPACE;
        cout << let << " |";
        for(int c = 0; c < 10; c++)
            cout << " " << board2[r][c] << " |";
        cout << endl << PARTITION << SPACE << PARTITION << endl;
    }
}

void initFleet(PlayerBoard &playerboard)
{   
    for(int r = 0; r < 10; r++)
    {
        for(int c = 0; c < 10; c++)
            playerboard.board[r][c] = ' ';
    }
    playerboard.ships[0].name = "carrier";
    playerboard.ships[0].size = CARRIER;
    playerboard.ships[0].hitcount = 0;
    playerboard.ships[1].name = "battleship";
    playerboard.ships[1].size = BATTLESHIP;
    playerboard.ships[1].hitcount = 0;
    playerboard.ships[2].name = "cruiser"; 
    playerboard.ships[2].size = CRUISER;
    playerboard.ships[2].hitcount = 0;
    playerboard.ships[3].name = "submarine";
    playerboard.ships[3].size = SUBMARINE;
    playerboard.ships[3].hitcount = 0;
    playerboard.ships[4].name = "destroyer";
    playerboard.ships[4].size = DESTROYER;
    playerboard.ships[4].hitcount = 0;
}

void boardSetup(PlayerBoard &pb1, PlayerBoard &pb2, bool computer)    
{
    int player1 = 1;
    char emptyBoard[10][10];
    for(int i = 0; i < 10; i++)
    {
        for(int k = 0; k < 10; k++)
        {
            emptyBoard[i][k] = ' ';
            pb1.board[i][k] = ' ';
            pb2.board[i][k] = ' ';
        }
    }
    cout << "Player 1 set your board.\n";
    displayBoards(pb1.board, emptyBoard); 
    for(int i = 0; i < 5; i++)
    {
        placeShip(pb1, i, computer, player1);
        displayBoards(pb1.board, emptyBoard); 
    }
    int player2 = 2;
    if(!computer)
        cout << "\n\n\n\nPlayer 2 set your board.\n";
    else  
        cout << "\n\n\n\nPlayer 2 (computer) is setting the board.\n";
    displayBoards(pb2.board, emptyBoard); 
    for(int i = 0; i < 5; i++)
    {
        placeShip(pb2, i, computer, player2);
        displayBoards(pb2.board, emptyBoard); 
    }
}

void placeShip(PlayerBoard &pb, int index, bool computer, int playerNum) 
{
    int row, col;
    char ori;
    getValidShipInfo(row, col, ori, pb, index, computer, playerNum);
    if(ori == 'h')
    {
        for(int i = 0; i < pb.ships[index].size; i++)
        {
            Point p;
            p.row = row;
            p.col = col + i;
            pb.ships[index].positions.push_back(p);
            pb.board[p.row][p.col] = 's';        
        }
    }
    else if(ori == 'v')
    {
        for(int i = 0; i < pb.ships[index].size; i++)
        {
            Point p;
            p.row = row + i;
            p.col = col;
            pb.ships[index].positions.push_back(p);
            pb.board[p.row][p.col] = 's';        
        }
    }
}

void getValidShipInfo(int &row, int &col, char &ori, PlayerBoard &pb, 
                      int index, bool computer, int playerNum)
{
    srand(500);
    bool valid = false;
    while(!valid)
    {
        if(computer && playerNum == 2)
        {
            row = rand() % 10;
            col = rand() % 10;
        }
        else
        {
            bool validCoor = false;
            while(!validCoor)
            {
                char r;
                cout << "Enter the starting coordinates of your ";
                cout << pb.ships[index].name << ": ";
                cin >> r >> col;
                row = r - 65;
                col -= 1;
                if(row < 10 && row >= 0 && col < 10 && col >= 0)
                      validCoor = true;
                else
                    cout << "Invalid coordinates. Please try again.\n";
            }
        }
        if(computer && playerNum == 2)
        {
            int num = rand() % 2;
            if(num == 0)
                ori = 'h';
            else if(num == 1)
                ori = 'v';
        }
        else
        {
            bool validOri = false;
            while(!validOri)
            {
                cout << "Enter the orientation of your carrier ";
                cout << "(horizontal(h) or vertical(v)): ";
                cin >> ori;
                if(ori == 'v' || ori == 'h')
                    validOri = true;
                else
                    cout << "Invalid orientation. Please try again.\n";
            }
        }
        if(spaceOccupied(pb, row, col, ori, pb.ships[index].size))
        {
            if((row + pb.ships[index].size >= 10) 
              || (col + pb.ships[index].size >= 10))
            {
                if(!(computer && playerNum == 2))
                    cout <<  "Error: Ship placement is outside the board.\n";
            }
            else
            {
                if(!(computer && playerNum == 2))
                    cout <<  "Error: Ship placement is outside the board.\n";
            }
        }
        else if(!spaceOccupied(pb, row, col, ori, pb.ships[index].size))
            valid = true;
    }
}

bool spaceOccupied(PlayerBoard pb, int row, int col, char ori, int shipSize) 
{
    bool occupied = false;
    if(ori == 'h')
    {
        for(int c = col; c < col + shipSize; c++)
        {
            if(pb.board[row][c] != ' ')
                occupied = true;
        }
    }
    else if(ori == 'v')
    {
        for(int r = row; r < row + shipSize; r++)
        {
            if(pb.board[r][col] != ' ')
                occupied = true;
        }
    }
    return occupied;
}

int playerTurn(PlayerBoard &enemy, char playerViewEnemy[][10], int playerNum) 
{
    char r;
    int row, col;
    cout << "Player " << playerNum << ":\n";
    bool validCoor = false;
    while(!validCoor)
    {
        cout << "Fire a shot: ";
        cin >> r >> col;
        row = r - 65; 
        col -= 1;
        if(row < 10 && row >= 0 && col < 10 && col >= 0 
           && playerViewEnemy[row][col] == ' ')
            validCoor = true;
        else
            cout << "Invalid.\n";
    }
    bool hit = update(enemy, row, col);
    if(hit)
    {
        enemy.board[row][col] = 'H';
        playerViewEnemy[row][col] = 'H';
        cout << "Hit!!!\n";
        for(int i = 0; i < 5; i++)
        {
            if(enemy.ships[i].hitcount == enemy.ships[i].size)
            {
                cout << "You sunk the ";
                cout << enemy.ships[i].name << "!!!\n";
                return playerNum;
            }
        }
    }
    else
    {
        enemy.board[row][col] = 'M';
        playerViewEnemy[row][col] = 'M';
        cout << "You Missed.\n";
    }  
    return 0;
}

bool update(PlayerBoard &enemy, int row, int col)        
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < enemy.ships[i].positions.size(); j++)
        {
            if(row == enemy.ships[i].positions[j].row 
            && col == enemy.ships[i].positions[j].col)
            {
                enemy.ships[i].hitcount++;
                return true;
            }
        }
    }
    return false;
}

int computerTurn(PlayerBoard &enemy, char playerViewEnemy[][10], 
                 int playerNum, int &prevRow, int &prevCol) 
{
    srand(time(0));
    int row, col;
    cout << "Player " << playerNum << " (computer):\n";
    cout << "Coordinates choosen: ";

    bool validCoor = false;
    while(!validCoor)
    {
        if(prevRow == -1 && prevCol == -1)
        {
            bool validCoor = false;
            while(!validCoor)
            {
                row = rand() % 10;
                col = rand() % 10;
                if(playerViewEnemy[row][col] == ' ')
                    validCoor = true;
            }
        }
        else
        { 
            int num = rand() % 4;
            if(num == 0)
            {
                row = prevRow;
                col = prevCol + 1;
            }
            else if(num == 1)
            {
                row = prevRow + 1;
                col = prevCol;
            } 
            else if(num == 2)
            {
                row = prevRow - 1;
                col = prevCol;
            }
            else
            {
                row = prevRow;
                col = prevCol - 1;
            }
        }
        if(playerViewEnemy[row][col] == ' ' && 
           row < 10 && row >= 0 && col < 10 && col >= 0)
            validCoor = true;
    }
    char boardRow = row + 65;
    cout << boardRow << " " << col + 1 << endl;
    bool hit = update(enemy, row, col);
    if(hit)
    {
        enemy.board[row][col] = 'H';
        playerViewEnemy[row][col] = 'H';
        prevRow = row;
        prevCol = col;
        cout << "Hit!!!\n";
        for(int i = 0; i < 5; i++)
        {
            if(enemy.ships[i].hitcount == enemy.ships[i].size)
            {
                cout << "Player 2 (computer) sunk the ";
                cout << enemy.ships[i].name << "!!!\n";
                return playerNum;
            }
        }
    }
    else
    {
        enemy.board[row][col] = 'M';
        playerViewEnemy[row][col] = 'M';
        cout << "Player 2 (computer) Missed.\n";
    }  
    return 0;
}