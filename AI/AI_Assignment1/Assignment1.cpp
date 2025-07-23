#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define N 3

struct State{
    vector<vector<int>> mat;
    int x, y;
    int depth;
    
    State(vector<vector<int>> b, int i, int j, int d) : mat(b), x(i), y(j), depth(d) {}
};

int row[] = {0, 0, -1, 1};
int col[] = {-1, 1, 0, 0};

bool isGoal(vector<vector<int>>& ini_state, vector<vector<int>>& final_state){
    if(ini_state == final_state){
        return true;
    }
    return false;
}

bool isValid(int x, int y){
    if(x >= 0 && x < N && y >= 0 && y < N){
        return true;
    }
    return false;
}

void pState(vector<vector<int>>& state){
    for(int i=0; i<state.size(); i++){
        for(int j=0; j<state[0].size(); j++){
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---------" << endl;
}

void solvePuzzle(vector<vector<int>>& start, vector<vector<int>>& end, int x, int y){
    queue<State> q;
    set<vector<vector<int>>> visited;
    
    q.push(State(start, x, y, 0));
    visited.insert(start);
    
    while(!q.empty()) {
        State curr = q.front();
        q.pop();
        cout << "Depth: " << curr.depth << endl;
        pState(curr.mat);
        if(isGoal(curr.mat, end)) {
            cout << "Goal Reached at Depth: " << curr.depth << endl;
            return;
        }
        for(int i=0; i<4; i++){
            int newX = curr.x + row[i];
            int newY = curr.y + col[i];
            if(isValid(newX, newY)) {
                vector<vector<int>> newMat = curr.mat;
                swap(newMat[curr.x][curr.y], newMat[newX][newY]);
                if(visited.find(newMat) == visited.end()) {
                    visited.insert(newMat);
                    q.push(State(newMat, newX, newY, curr.depth+1));
                }
            }
        }
    }
    cout << "No Solution Found" << endl;
}

int main(){
    vector<vector<int>> mat1 = {
        {1,2,3},
        {4,0,6},
        {7,5,8}
    };
    int x = 1;
    int y = 1;
    
    vector<vector<int>> mat2 = {
        {1,2,3},
        {4,5,6},
        {7,8,0}        
    };
    
    cout << "Initial State: " << endl;
    pState(mat1);
    solvePuzzle(mat1, mat2, x, y);
    
    return 0;
}
