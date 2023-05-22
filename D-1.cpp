#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    std::string str1;
    std::string str2;
    std::cin >> str1 >> str2;
    std::string str;
    str = str1 + '#' + str2;
    std::vector<size_t> prefix(str.size(), 0);
    for (size_t i = 1; i < str.size(); ++i) {
        size_t value_of_i = prefix[i - 1];
        while (value_of_i > 0 && str[i] != str[value_of_i]) {
            value_of_i = prefix[value_of_i - 1];
        }
        if (str[i] == str[value_of_i]) {
            value_of_i++;
        }
        prefix[i] = value_of_i;
        if (i > str1.size() && value_of_i == 0) {
            std::cout << "Yes";
            return 0;
        }
    }
    size_t i = str.size() - 1;
    std::vector<std::string> answer;
    while (str[i] != '#') {
        answer.push_back(str1.substr(0, prefix[i]));
        i -= prefix[i];
    }
    std::reverse(answer.begin(), answer.end());
    std::cout << "No\n";
    for (size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << " ";
    }
    return 0;
}
