#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>



enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int sol1(std::vector<std::vector<char>>& mat) {
    std::pair<int, int> guardPos;
    std::vector<std::vector<bool>> visited(mat.size(), std::vector<bool> (mat[0].size(), false));
    enum Direction dir;
    bool foundGuard = false;
    int cnt = 1;

    // find guard Position and initial direction
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (mat[i][j] == '^') {
                dir = UP;
                guardPos = std::make_pair(i,j);
                foundGuard = true;
                break;
            } else if (mat[i][j] == 'v') {
                dir = DOWN;
                guardPos = std::make_pair(i,j);
                foundGuard = true;
                break;
            } else if (mat[i][j] == '>') {
                dir = RIGHT;
                guardPos = std::make_pair(i,j);
                foundGuard = true;
                break;
            } else if (mat[i][j] == '<') {
                dir = LEFT;
                guardPos = std::make_pair(i,j);
                foundGuard = true;
                break;
            }
        }

        if (foundGuard) break;
    }

    visited[guardPos.first][guardPos.second] = true;

    /* 
        Simulate the ruleset, each tile it moves on will be marked as visited and cnt will be incremented if the tile is already marked
        visited cnt will not be incremented. This will be done until one of the coordinates of guardPos is out of bounds 
    */ 

    while (true) {
        switch (dir) {
            case UP:
                guardPos.first -= 1;
                break;
            case DOWN:
                guardPos.first += 1;
                break;
            case LEFT:
                guardPos.second -= 1;
                break;
            case RIGHT:
                guardPos.second += 1;
                break;
        }

        

        if (guardPos.first < 0 || guardPos.first >= mat.size() || guardPos.second < 0 || guardPos.second >= mat[0].size()) {
            break;  
        }
        
        if (!visited[guardPos.first][guardPos.second]) {
            cnt++;
            visited[guardPos.first][guardPos.second] = true;
        }
    
        switch (dir) {
            case UP: 
                if ((guardPos.first - 1) >= 0) {
                    if (mat[guardPos.first - 1][guardPos.second] == '#') dir = RIGHT; 
                }
                break;
            case DOWN:
                if ((guardPos.first + 1) < mat.size()) {
                    if (mat[guardPos.first + 1][guardPos.second] == '#') dir = LEFT; 
                } 
                break;
            case LEFT:
                if ((guardPos.second - 1) >= 0) {
                    if (mat[guardPos.first][guardPos.second - 1] == '#') dir = UP; 
                }
                break;
            case RIGHT:
                if ((guardPos.first - 1) < mat[0].size()) {
                    if (mat[guardPos.first][guardPos.second + 1] == '#') dir = DOWN; 
                }
                break;
        }
    }


    return cnt;
}


int main() {
    std::ifstream file("input.txt"); 
    std::vector<std::vector<char>> input; 

    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::string line;
    
    while (std::getline(file, line)) { 
        if (!line.empty()) {
            std::istringstream ss(line); 
            std::vector<char> chars; 
            char character;

            while (ss >> character) {
                chars.push_back(character);
            }

            input.push_back(chars); 
        }

    }

    int cnt = sol1(input);

    std::cout << "The solution is: " << cnt << std::endl;



    return 0;
}