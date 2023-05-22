#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

size_t Index(size_t num, size_t sq_n, size_t size, size_t n) {
    if (num < sq_n) {
        return num - 1;
    }
    return size - (n / num);
}

size_t PrimesBelow(size_t n) {
    size_t answer = 0;
    std::set<size_t> set;
    for (size_t i = 1; i * i <= n; ++i) {
        set.emplace(i);
        set.emplace(n / i);
    }
    std::vector<size_t> v_set;
    for (auto i : set) {
        v_set.push_back(i);
    }
    std::sort(v_set.begin(), v_set.end());
    size_t sq_n = 1;
    while (sq_n * sq_n < n) {
        sq_n++;
    }
    std::vector<size_t> dp(v_set.size());
    for (size_t i = 0; i < v_set.size(); ++i) {
        dp[i] = v_set[i];
    }
    size_t primes = 0;
    for (size_t p = 2; p <= sq_n; ++p) {
        if (dp[Index(p, sq_n, v_set.size(), n)] != dp[Index(p - 1, sq_n, v_set.size(), n)]) {
            primes++;
            for (size_t i = v_set.size() - 1; i >= 0; --i) {
                if (v_set[i] < p * p) {
                    break;
                }
                dp[i] -= dp[Index(v_set[i] / p, sq_n, v_set.size(), n)] - primes;
            }
        }
    }
    answer = dp[Index(n, sq_n, v_set.size(), n)] - 1;
    return answer;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    std::cout << PrimesBelow(n);
    return 0;
}
