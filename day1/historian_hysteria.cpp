#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int solution2(const std::vector<int>& list1, const std::vector<int>& list2) {
    int sum = 0;

    for (int i = 0; i < list1.size(); ++i) {
        int score = 0;
        
        for (int j = 0; j < list2.size(); ++j) {
            if (list1[i] == list2[j]) {
                score++;
            }
        }

        if (score != 0) {
            sum += (list1[i] * score);
        }
    }

    return sum;
}

int main() {
    std::string filePath = "input.txt"; // Input file path
    std::ifstream file(filePath);  // Open the file for reading
    std::vector<int> col1;
    std::vector<int> col2;


    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::istringstream stream(line);
            int num1, num2;
            if (stream >> num1 >> num2) {
                col1.push_back(num1);
                col2.push_back(num2);
            } else {
                std::cerr << "Skipping invalid line (could not parse numbers): " << line << std::endl;
            }
        }
    }

    file.close();

    if (!col1.empty() && !col2.empty()) {
        int result = solution2(col1, col2);
        
        std::cout << "The solution is: " << result << std::endl;
    } else {
        std::cerr << "No valid data to process." << std::endl;
    }

    return 0;
}
