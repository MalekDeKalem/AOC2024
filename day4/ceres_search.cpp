#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

int sol1(std::vector<std::vector<char>>& mat) {

    int X = 23;
    int M = 12;
    int A = 0;
    int S = 18;

    int cnt = 0;

    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            /* If X was found check the next 3 chars if they're M A and S in that order
                do that vertically if possible boundwise horizontally and diagonally  
                so in total you have to check 8 different direction 4 diagonally 2 horizontally and 2 vertically
            */ 


           // check horizontally
           if ((j + 3) < mat[i].size()) {
                if ((mat[i][j] - 'A') == X && (mat[i][j+1] - 'A') == M && (mat[i][j+2] - 'A') == A && (mat[i][j+3] - 'A') == S) cnt++;
           }

            if ((j - 3) >= 0) {
                if ((mat[i][j] - 'A') == X && (mat[i][j-1] - 'A') == M && (mat[i][j-2] - 'A') == A && (mat[i][j-3] - 'A') == S) cnt++;
           }

           // check vertically 
            if ((i + 3) < mat.size()) {
                if ((mat[i][j] - 'A') == X && (mat[i+1][j] - 'A') == M && (mat[i+2][j] - 'A') == A && (mat[i+3][j] - 'A') == S) cnt++;
            }

            if ((i - 3) >= 0) {
                if ((mat[i][j] - 'A') == X && (mat[i-1][j] - 'A') == M && (mat[i-2][j] - 'A') == A && (mat[i-3][j] - 'A') == S) cnt++;
            }

            // checkt diagonally
            if ((i + 3) < mat.size() && (j + 3) < mat[i].size()) {
                if ((mat[i][j] - 'A') == X && (mat[i+1][j+1] - 'A') == M && 
                    (mat[i+2][j+2] - 'A') == A && (mat[i+3][j+3] - 'A') == S) cnt++;
            }

            if ((i + 3) < mat.size() && (j - 3) >= 0) {
                if ((mat[i][j] - 'A') == X && (mat[i+1][j-1] - 'A') == M && 
                    (mat[i+2][j-2] - 'A') == A && (mat[i+3][j-3] - 'A') == S) cnt++;
            }

            if ((i - 3) >= 0 && (j + 3) < mat[i].size()) {
                if ((mat[i][j] - 'A') == X && (mat[i-1][j+1] - 'A') == M && 
                    (mat[i-2][j+2] - 'A') == A && (mat[i-3][j+3] - 'A') == S) cnt++;
            }

            if ((i - 3) >= 0 && (j - 3) >= 0) {
                if ((mat[i][j] - 'A') == X && (mat[i-1][j-1] - 'A') == M && 
                    (mat[i-2][j-2] - 'A') == A && (mat[i-3][j-3] - 'A') == S) cnt++;
            }

        }
    }

    return cnt;
}

int sol2(std::vector<std::vector<char>>& mat) {
    int M = 12;
    int A = 0;
    int S = 18;

    int cnt = 0;

    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if ((mat[i][j] - 'A') == M) {
                if ((i + 2) < mat.size() && (j + 2) < mat[i].size()) {
                    // Check for M.S pattern and for M.M pattern
                    if ((mat[i+1][j+1] - 'A') == A && 
                        (mat[i][j+2] - 'A') == S && 
                        (mat[i+2][j+2] - 'A') == S && 
                        (mat[i+2][j] - 'A') == M) {
                        cnt++;
                    } else if ((mat[i+1][j+1] - 'A') == A &&
                        (mat[i][j+2] - 'A') == M &&
                        (mat[i+2][j] - 'A') == S &&
                        (mat[i+2][j+2] - 'A') == S) {
                        cnt++;
                    }
                }
            } else if ((mat[i][j] - 'A') == S) {
                if ((i + 2) < mat.size() && (j + 2) < mat[i].size()) {
                    // Check for S.M pattern and for S.S pattern
                    /*
                        S.M     S.S
                        .A.     .A.
                        S.M     M.M
                    */
                    if ((mat[i+1][j+1] - 'A') == A && 
                        (mat[i][j+2] - 'A') == S && 
                        (mat[i+2][j+2] - 'A') == M && 
                        (mat[i+2][j] - 'A') == M) {
                        cnt++;
                    } else if ((mat[i+1][j+1] - 'A') == A &&
                        (mat[i+2][j] - 'A') == S &&
                        (mat[i+2][j+2] - 'A') == M &&
                        (mat[i][j+2] - 'A') == M) {
                        cnt++;
                    }
                }
            }
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

    int ans = sol2(input);

    std::cout << ans << std::endl;

    return 0;
}