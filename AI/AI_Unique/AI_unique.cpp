#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int dRow[4] = {-1, 1, 0, 0};
int dCol[4] = {0, 0, -1, 1};

struct Node {
    int row, col;
    int hCost;
    Node* parent;

    Node(int r, int c, int h, Node* p = nullptr)
        : row(r), col(c), hCost(h), parent(p) {}
};

struct CompareHCost {
    bool operator()(Node* a, Node* b) {
        return a->hCost > b->hCost;
    }
};

int manhattanDistance(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

bool isValid(int row, int col, const vector<vector<int>>& maze) {
    return row >= 0 && row < maze.size() &&
           col >= 0 && col < maze[0].size() &&
           maze[row][col] == 0;
}

void printMazeWithPath(vector<vector<int>> maze, Node* endNode) {
    Node* current = endNode;
    while (current != nullptr) {
        maze[current->row][current->col] = 7;
        current = current->parent;
    }

    cout << "\nMaze with Path (7 = path):\n";
    for (auto& row : maze) {
        for (auto& cell : row)
            cout << cell << " ";
        cout << endl;
    }
}

bool greedyBestFirstSearch(vector<vector<int>>& maze, pair<int,int> start, pair<int,int> goal) {
    int rows = maze.size(), cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    priority_queue<Node*, vector<Node*>, CompareHCost> openList;

    int h = manhattanDistance(start.first, start.second, goal.first, goal.second);
    Node* startNode = new Node(start.first, start.second, h);
    openList.push(startNode);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        int r = current->row, c = current->col;
        visited[r][c] = true;

        if (r == goal.first && c == goal.second) {
            cout << "\nPath found using Greedy Best-First Search!\n";
            printMazeWithPath(maze, current);
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = r + dRow[i];
            int newCol = c + dCol[i];

            if (isValid(newRow, newCol, maze) && !visited[newRow][newCol]) {
                int hNew = manhattanDistance(newRow, newCol, goal.first, goal.second);
                Node* neighbor = new Node(newRow, newCol, hNew, current);
                openList.push(neighbor);
                visited[newRow][newCol] = true;
            }
        }
    }

    cout << "\nNo path found!\n";
    return false;
}

int main() {
    // 0 = free cell, 1 = wall
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0},
        {1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal  = {4, 5};

    cout << "Original Maze (0 = free, 1 = wall):\n";
    for (auto& row : maze) {
        for (auto& cell : row)
            cout << cell << " ";
        cout << endl;
    }

    greedyBestFirstSearch(maze, start, goal);

    return 0;
}
