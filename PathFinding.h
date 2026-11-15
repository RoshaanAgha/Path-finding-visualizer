
#ifndef PathFinding_H
#define PathFinding_H

#include <iostream>
using namespace std;

const int ROWS = 10;
const int COLS = 10;
const int SIZE = ROWS * COLS;

class Node
{
public:
    int row;
    int col;
    bool isWall;
    bool isVisited;
    int distance;

    Node()
    {
        row = 0;
        col = 0;
        isWall = false;
        isVisited = false;
        distance = INF;
    }
};

class Grid
{
public:
    Node nodes[ROWS][COLS];
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    Grid()
    {
        startRow = 0;
        startCol = 0;
        endRow = ROWS - 1;
        endCol = COLS - 1;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                nodes[i][j].row = i;
                nodes[i][j].col = j;
            }
        }
    }

