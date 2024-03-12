#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int FLEET_SIZE = 5, CARRIER = 5, BATTLESHIP = 4, CRUISER = 3;
const int SUBMARINE = 3, DESTROYER = 2;
const string SPACE = "          ";
const string PARTITION = "  -----------------------------------------";

struct Point
{
    int row;      
    int col;      
};

struct ship
{
    string name;     
    int size;          
    int hitcount;      
    vector<Point> positions;   
};

struct PlayerBoard
{
    char board[10][10];      
    ship ships[FLEET_SIZE];  
};

void displayBoards(char [][10], char [][10]);  

void initFleet(PlayerBoard &);    

void boardSetup(PlayerBoard &pb1, PlayerBoard &, bool);    

void placeShip(PlayerBoard &, int, bool, int);  

void getValidShipInfo(int &, int &, char &, PlayerBoard &, int, bool, int);

bool spaceOccupied(PlayerBoard, int, int, char, int);   

int playerTurn(PlayerBoard &, char [][10], int);   

bool update(PlayerBoard &, int, int);             

int computerTurn(PlayerBoard &, char [][10], int, int &, int &);  

#include "functions.cpp"

#endif