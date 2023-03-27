#include <iostream>
#include <vector>
#include <algorithm>

bool Ispref(std::string& s, std::string& t, std::vector<std::string>& answer) {
    for (size_t i = 0; i < t.size(); ++i) {
        if (t[i] == s[0] && i > 0) {
            if (Ispref(s, t.substr(i), answer)) {
                answer.push_back(t.substr(0, i));
                return true;
            }
        }
        if (t[i] != s[i]) {
            if (t[i] == s[0]) {
                if (Ispref(s, t.substr(i), answer)) {
                    answer.push_back(t.substr(0, i));
                    return true;
                }
            } else {
                return false;
            }
        }
    }
    answer.push_back(t);
    return true;
}

int main() {
    std::string str1;
    std::string str2;
    std::cin >> str1 >> str2;
    std::vector<std::string> answer;
    if (Ispref(str1, str2, answer)) {
        std::cout << "No"
                  << "\n";
        std::reverse(answer.begin(), answer.end());
        for (size_t i = 0; i < answer.size(); ++i) {
            std::cout << answer[i] << " ";
        }
    } else {
        std::cout << "Yes";
    }
    return 0;
}