#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int sol1(std::vector<std::vector<int>>& input) {
    int ans = 0;

    for (int i = 0; i < input.size(); i++) {
        if (input[i].size() < 2) continue;

        bool isIncreasing = input[i][0] < input[i][1];
        
        bool isValid = true;

        for (int j = 1; j < input[i].size(); j++) {
            if ((isIncreasing && input[i][j] <= input[i][j-1]) || 
                (!isIncreasing && input[i][j] >= input[i][j-1])) {
                isValid = false;
                break;
            }

            if ((std::abs(input[i][j] - input[i][j-1]) < 1 || 
                          std::abs(input[i][j] - input[i][j-1]) > 3)
                ) {
                isValid = false;
                break;
            }
        }

        if (isValid) ans++;
    }

    return ans;
}

int sol2(std::vector<std::vector<int>>& input) {
    int ans = 0;

    for (int i = 0; i < input.size(); i++) {
        if (input[i].size() < 2) continue;

        auto isValid = [&](std::vector<int>& row) {
            bool isIncreasing = row[0] < row[1];
            for (int j = 1; j < row.size(); j++) {
                if ((isIncreasing && row[j] <= row[j-1]) || 
                    (!isIncreasing && row[j] >= row[j-1])) {
                    return false;
                }
                if (std::abs(row[j] - row[j-1]) < 1 || 
                    std::abs(row[j] - row[j-1]) > 3) {
                    return false;
                }
            }
            return true;
        };

        if (isValid(input[i])) {
            ans++;
            continue;
        }

        bool canBeValid = false;
        for (int j = 0; j < input[i].size(); j++) {
            std::vector<int> tempRow = input[i];
            tempRow.erase(tempRow.begin() + j);

            if (isValid(tempRow)) {
                canBeValid = true;
                break;
            }
        }

        if (canBeValid) ans++;
    }

    return ans;
}



int main() {
    std::ifstream file("input.txt"); 
    std::vector<std::vector<int>> input; 

    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) { 
        if (!line.empty()) {
            std::istringstream ss(line); 
            std::vector<int> numbers; 
            int number;

            while (ss >> number) {
                numbers.push_back(number);
            }

            input.push_back(numbers); 
        }

    }

    file.close(); 

    int ans = sol2(input);

    printf("The solution is %d\n", ans);


    return 0;
}

