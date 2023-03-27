#include <vector>
#include <iostream>
const size_t kAlphabetSize = 128;

std::vector<size_t> RadixSortString(std::string& array) {
    std::vector<size_t> counter(kAlphabetSize, 0);
    std::vector<size_t> sorted(array.size());
    for (size_t i = 0; i < array.size(); ++i) {
        ++counter[static_cast<size_t>(array[i])];
    }
    for (size_t i = 1; i < kAlphabetSize; ++i) {
        counter[i] += counter[i - 1];
    }
    for (size_t i = 0; i < array.size(); ++i) {
        sorted[--counter[array[array.size() - i - 1]]] = array.size() - i - 1;
    }
    return sorted;
}

std::vector<size_t> SufArray(std::string input_str) {
    std::vector<size_t> sufarr(input_str.size());
    std::string str = input_str + '\0';
    size_t n = str.size();
    std::vector<size_t> p = RadixSortString(str);
    std::vector<size_t> c(n, 0);
    size_t max_c = 0;
    for (size_t i = 1; i < n; ++i) {
        c[p[i]] = c[p[i - 1]];
        if (str[p[i]] != str[p[i - 1]]) {
            c[p[i]]++;
        }
        if (c[p[i]] > max_c) {
            max_c = c[p[i]];
        }
    }
    for (size_t k = 0; max_c < n - 1; k++) {
        size_t len = 1 << k;
        std::vector<std::pair<size_t, size_t>> c_pairs;
        std::vector<size_t> new_p(n);
        std::vector<size_t> new_c(n);
        for (size_t i = 0; i < n; ++i) {
            if (p[i] < len) {
                new_p[i] = p[i] + n - len;
            } else {
                new_p[i] = p[i] - len;
            }
        }
        std::vector<size_t> counter(n, 0);
        for (size_t i = 0; i < n; ++i) {
            ++counter[c[i]];
        }
        for (size_t i = 1; i < n; ++i) {
            counter[i] += counter[i - 1];
        }
        for (size_t j = 0; j < n; ++j) {
            size_t i = n - 1 - j;
            p[--counter[c[new_p[i]]]] = new_p[i];
        }
        new_c[p[0]] = 0;
        max_c = 0;
        for (size_t i = 1; i < n; ++i) {
            new_c[p[i]] = new_c[p[i - 1]];
            if (c[p[i]] != c[p[i - 1]]) {
                ++new_c[p[i]];
            } else if (c[p[i] + len] != c[p[i - 1] + len]) {
                ++new_c[p[i]];
            }
            if (max_c < new_c[p[i]]) {
                max_c = new_c[p[i]];
            }
        }
        c = new_c;
    }
    sufarr = p;
    return sufarr;
}

int main() {
    std::string str;
    getline(std::cin, str);
    std::vector<size_t> answer = SufArray(str);
    for (size_t i = 1; i < answer.size(); ++i) {
        if (answer[i] < answer.size() - 1) {
            std::cout << answer[i] + 1;
        } else {
            std::cout << 0;
        }
        std::cout << " ";
    }
    return 0;
}