#ifndef PathFinding_H
#define PathFinding_H

#include <iostream>
using namespace std;

const int ROWS = 10;
const int COLS = 10;
const int SIZE = ROWS * COLS;
const int MAX_BUFFER = SIZE * 4;
const int INF = 999999;
const int MIN_COST = 1;
const int MAX_COST = 9;

class Node
{
public:
    int row;
    int col;
    bool isWall;
    bool isVisited;
    int distance;
    int cost;
    int parentRow;
    int parentCol;

    Node()
    {
        row = 0;
        col = 0;
        isWall = false;
        isVisited = false;
        distance = INF;
        cost = MIN_COST;
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
            nodes[row][col].cost = MIN_COST;
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

    void setCost(int row, int col, int cost)
    {
        if (!isValid(row, col))
        {
            cout << "Invalid position!" << endl;
            return;
        }

        if (nodes[row][col].isWall)
        {
            cout << "Cannot set terrain on a wall! Remove the wall first." << endl;
            return;
        }

        if (cost < MIN_COST || cost > MAX_COST)
        {
            cout << "Invalid cost! Must be between " << MIN_COST
                 << " and " << MAX_COST << "." << endl;
            return;
        }

        nodes[row][col].cost = cost;
        resetSearch();
        cout << "Cell (" << row << ", " << col << ") now costs " << cost << " to enter." << endl;
    }

    void clearTerrain()
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                nodes[i][j].cost = MIN_COST;
            }
        }

        resetSearch();
        cout << "All terrain reset to normal!" << endl;
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
                else if (nodes[i][j].cost > MIN_COST)
                    cout << nodes[i][j].cost << " ";
                else
                    cout << "- ";
            }

            cout << endl;
        }
    }
};

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

class Stack
{
private:
    int arr[MAX_BUFFER];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    bool isEmpty() const
    {
        return top == -1;
    }

    void push(int value)
    {
        if (top < MAX_BUFFER - 1)
        {
            top++;
            arr[top] = value;
        }
    }

    int pop()
    {
        if (!isEmpty())
        {
            int value = arr[top];
            top--;
            return value;
        }

        return -1;
    }
};

class PriorityQueue
{
private:
    int heap[MAX_BUFFER];
    int priority[MAX_BUFFER];
    int size;

    void swapValues(int i, int j)
    {
        int temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

        temp = priority[i];
        priority[i] = priority[j];
        priority[j] = temp;
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (priority[index] < priority[parent])
            {
                swapValues(index, parent);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int index)
    {
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && priority[left] < priority[smallest])
            {
                smallest = left;
            }

            if (right < size && priority[right] < priority[smallest])
            {
                smallest = right;
            }

            if (smallest != index)
            {
                swapValues(index, smallest);
                index = smallest;
            }
            else
            {
                break;
            }
        }
    }

public:
    PriorityQueue()
    {
        size = 0;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void enqueue(int value, int cost)
    {
        if (size < MAX_BUFFER)
        {
            heap[size] = value;
            priority[size] = cost;

            heapifyUp(size);
            size++;
        }
    }

    int dequeue()
    {
        if (isEmpty())
            return -1;

        int value = heap[0];
        size--;

        if (size > 0)
        {
            heap[0] = heap[size];
            priority[0] = priority[size];
            heapifyDown(0);
        }

        return value;
    }

    int getPriority() const
    {
        if (!isEmpty())
            return priority[0];

        return INF;
    }
};

class SearchResult
{
public:
    bool found;
    int visitedCount;
    int pathLength;   // number of steps
    int pathCost;     // NEW: total terrain cost of the path
    int path[SIZE];
    int pathSize;

    SearchResult()
    {
        found = false;
        visitedCount = 0;
        pathLength = 0;
        pathCost = 0;
        pathSize = 0;
    }
};

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int absoluteValue(int number)
{
    return (number < 0) ? -number : number;
}

bool validNeighbor(const Grid& grid, int row, int col)
{
    return grid.isValid(row, col) && !grid.nodes[row][col].isWall;
}

void prepareGrid(Grid& grid)
{
    grid.resetSearch();
    grid.nodes[grid.startRow][grid.startCol].distance = 0;
}

SearchResult getResult(const Grid& grid, bool found)
{
    SearchResult result;
    result.found = found;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid.nodes[i][j].isVisited)
            {
                result.visitedCount++;
            }
        }
    }

    if (found)
    {
        int row = grid.endRow;
        int col = grid.endCol;

        while (row != -1 && col != -1 && result.pathSize < SIZE)
        {
            result.path[result.pathSize] = row * COLS + col;
            result.pathSize++;

            int newRow = grid.nodes[row][col].parentRow;
            int newCol = grid.nodes[row][col].parentCol;

            row = newRow;
            col = newCol;
        }

        for (int i = 0; i < result.pathSize / 2; i++)
        {
            int temp = result.path[i];
            result.path[i] = result.path[result.pathSize - 1 - i];
            result.path[result.pathSize - 1 - i] = temp;
        }

        result.pathLength = result.pathSize - 1;

        // NEW: total cost = cost of entering every cell on the path except the start
        for (int i = 1; i < result.pathSize; i++)
        {
            int r = result.path[i] / COLS;
            int c = result.path[i] % COLS;
            result.pathCost += grid.nodes[r][c].cost;
        }
    }

    return result;
}
SearchResult BFS(Grid& grid)
{
    prepareGrid(grid);

    Queue q;
    int startIdx = grid.startRow * COLS + grid.startCol;
    q.enqueue(startIdx);

    bool found = false;

    while (!q.isEmpty())
    {
        int current = q.dequeue();
        int row = current / COLS;
        int col = current % COLS;

        if (grid.nodes[row][col].isVisited)
            continue;

        grid.nodes[row][col].isVisited = true;

        if (grid.isEnd(row, col))
        {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (validNeighbor(grid, newRow, newCol) &&
                grid.nodes[newRow][newCol].distance == INF)
            {
                grid.nodes[newRow][newCol].distance =
                    grid.nodes[row][col].distance + 1;

                grid.nodes[newRow][newCol].parentRow = row;
                grid.nodes[newRow][newCol].parentCol = col;

                q.enqueue(newRow * COLS + newCol);
            }
        }
    }

    return getResult(grid, found);
}

#endif
