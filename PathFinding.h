#ifndef PathFinding_H
#define PathFinding_H

#include <iostream>
using namespace std;

const int ROWS = 10;
const int COLS = 10;
const int SIZE = ROWS * COLS;
const int MAX_BUFFER = SIZE * 4;
const int INF = 999999;

class Node
{
public:
    int row;
    int col;
    bool isWall;
    bool isVisited;
    int distance;
    int parentRow;
    int parentCol;

    Node()
    {
        row = 0;
        col = 0;
        isWall = false;
        isVisited = false;
        distance = INF;
        parentRow = -1;
        parentCol = -1;
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

    bool isValid(int row, int col) const
    {
        return row >= 0 && row < ROWS &&
               col >= 0 && col < COLS;
    }

    bool isStart(int row, int col) const
    {
        return row == startRow && col == startCol;
    }

    bool isEnd(int row, int col) const
    {
        return row == endRow && col == endCol;
    }

    void setStartEnd(int sRow, int sCol, int eRow, int eCol)
    {
        if (!isValid(sRow, sCol) || !isValid(eRow, eCol))
        {
            cout << "Invalid coordinates! Must be within 0-" << ROWS - 1
                 << " and 0-" << COLS - 1 << "." << endl;
            return;
        }

        if (sRow == eRow && sCol == eCol)
        {
            cout << "Start and End positions cannot be the same cell!" << endl;
            return;
        }

        if (nodes[sRow][sCol].isWall || nodes[eRow][eCol].isWall)
        {
            cout << "Cannot place Start or End on a wall! Remove the wall first." << endl;
            return;
        }

        startRow = sRow;
        startCol = sCol;
        endRow = eRow;
        endCol = eCol;

        resetSearch();
        cout << "Start set to (" << startRow << ", " << startCol
             << ") and End set to (" << endRow << ", " << endCol << ")." << endl;
    }

    void addWall(int row, int col)
    {
        if (isValid(row, col) && !isStart(row, col) && !isEnd(row, col))
        {
            nodes[row][col].isWall = true;
            resetSearch();
            cout << "Wall added!" << endl;
        }
        else
        {
            cout << "Invalid position!" << endl;
        }
    }

    void removeWall(int row, int col)
    {
        if (isValid(row, col))
        {
            nodes[row][col].isWall = false;
            resetSearch();
            cout << "Wall removed!" << endl;
        }
        else
        {
            cout << "Invalid position!" << endl;
        }
    }

    void clearWalls()
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                nodes[i][j].isWall = false;
            }
        }

        resetSearch();
        cout << "All walls cleared!" << endl;
    }

    void resetSearch()
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                nodes[i][j].isVisited = false;
                nodes[i][j].distance = INF;
                nodes[i][j].parentRow = -1;
                nodes[i][j].parentCol = -1;
            }
        }
    }

    void display(const int path[], int pathSize) const
    {
        cout << endl;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                int position = i * COLS + j;
                bool isPath = false;

                if (path != NULL)
                {
                    for (int k = 0; k < pathSize; k++)
                    {
                        if (path[k] == position)
                        {
                            isPath = true;
                            break;
                        }
                    }
                }

                if (isStart(i, j))
                    cout << "S ";
                else if (isEnd(i, j))
                    cout << "E ";
                else if (nodes[i][j].isWall)
                    cout << "# ";
                else if (isPath)
                    cout << "* ";
                else if (nodes[i][j].isVisited)
                    cout << ". ";
                else
                    cout << "- ";
            }

            cout << endl;
        }
    }
};

#endif
class Queue
{
private:
    int arr[SIZE];
    int front;
    int rear;

public:
    Queue()
    {
        front = 0;
        rear = -1;
    }

    bool isEmpty() const { return front > rear; }

    void enqueue(int value)
    {
        if (rear < SIZE - 1)
        {
            rear++;
            arr[rear] = value;
        }
    }

    int dequeue()
    {
        if (!isEmpty())
        {
            int value = arr[front];
            front++;
            return value;
        }
        return -1;
    }
};
