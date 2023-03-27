#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <algorithm>
const size_t kHashConstant = 31;
size_t Hash(std::string pattern, size_t way) {
    size_t hash = 0;
    size_t to_pow = 1;

    if (way == 0) {
        for (size_t i = 0; i < pattern.size(); ++i) {
            hash += pattern[i] * to_pow;
            if (i < pattern.size() - 1) {
                to_pow *= kHashConstant;
            }
        }
    } else {
        for (size_t i = 0; i < pattern.size(); ++i) {
            hash += pattern[pattern.size() - 1 - i] * to_pow;
            if (i < pattern.size() - 1) {
                to_pow *= kHashConstant;
            }
        }
    }
    return hash;
}

void PalindromCombinations(std::vector<std::string> str_array) {
    std::unordered_map<std::string, size_t> map;
    std::vector<std::pair<size_t, size_t>> answer;
    for (size_t i = 0; i < str_array.size(); ++i) {
        map[std::string(str_array[i].rbegin(), str_array[i].rend())] = i + 1;
    }


    for (size_t i = 0; i < str_array.size(); ++i) {
        std::string str = str_array[i];
        for (size_t j = 0; j < str.size(); ++j) {

            std::string right = str.substr(j + 1);
            size_t right_hash_left = Hash(right, 0);
            size_t right_hash_right = Hash(right, 1);
            std::string left = str.substr(0, j + 1);
            size_t left_hash_left = Hash(left, 0);
            size_t left_hash_right = Hash(left, 1);
            if (right_hash_right == right_hash_left && map.count(left) > 0 && map[left] != i + 1) {
                answer.emplace_back(i + 1, map[left]);
            }

            if (left_hash_right == left_hash_left && map.count(right) > 0 && map[right] != i + 1) {
                answer.emplace_back(map[right], i + 1);
            }
        }
    }
    std::sort(answer.begin(), answer.end());

    std::cout << answer.size() << "\n";
    for (auto item : answer) {
        std::cout << item.first << " " << item.second << "\n";
    }
}

int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<std::string> str_array;
    for (size_t i = 0; i < n; ++i) {
        std::string input;
        std::cin >> input;
        str_array.push_back(input);
    }
    PalindromCombinations(str_array);

    return 0;
}