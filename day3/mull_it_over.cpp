#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

int sol1(std::string input) {
    std::regex pattern(R"(mul\(\d+,\d+\))");
    std::smatch match;
    std::string result;

    auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = std::sregex_iterator();

    for (auto it = matches_begin; it != matches_end; ++it) {
        result += it->str() + " "; 
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    std::stringstream ss(result);
    std::string token;
    int ans = 0;

    while (std::getline(ss, token, '(')) {
        std::getline(ss, token, ')');
        std::stringstream pair_stream(token);
        std::string number;
        std::vector<int> nums;

        while (std::getline(pair_stream, number, ',')) {
            nums.push_back(std::stoi(number));
        }

        ans += nums[0] * nums[1];
    }

    return ans;
}

std::tuple<int, bool> sol2(std::string input, bool doFlag) {
    std::regex pattern(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
    std::smatch match;
    std::string result;

    auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = std::sregex_iterator();

    for (auto it = matches_begin; it != matches_end; ++it) {
        result += it->str() + " "; 
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    std::stringstream ss(result);
    std::string token;
    int ans = 0;

    while (ss >> token) {
        if (token == "don't()") {
            doFlag = false;
        } else if (token == "do()") {
            doFlag = true;
        } else if (token.find("mul(", 0) == 0) {
            size_t openParen = token.find('(');
            size_t comma = token.find(',');
            size_t closeParen = token.find(')');

            if (openParen != std::string::npos && comma != std::string::npos && closeParen != std::string::npos) {
                int a = std::stoi(token.substr(openParen + 1, comma - openParen - 1));
                int b = std::stoi(token.substr(comma + 1, closeParen - comma - 1));

                if (doFlag) {
                    ans += a * b;
                } 
            }
        }
    }

    return std::make_tuple(ans, doFlag);
}

int main() {
    std::string filePath = "input.txt";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    int ans = 0;
    std::string line;
    bool doFlag = true;
    while (getline(file, line)) {

        // Solution 1
        // int res = sol1(line);
        // ans += res;


        // Solution 2
        auto [res, newFlag] = sol2(line, doFlag);
        ans += res;
        doFlag = newFlag;
    }

    std::cout << "The solution is: " << ans << std::endl;

    file.close();

    return 0;
}


