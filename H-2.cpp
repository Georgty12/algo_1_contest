#define _USE_MATH_DEFINES
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using Complex = std::complex<double>;

std::vector<size_t> PrecalcRev(size_t n, size_t ln) {
    std::vector<size_t> rev;
    for (size_t i = 0; i < n; ++i) {
        rev.push_back(0);
        for (size_t j = 0; j < ln; ++j) {
            if (i & (1 << j)) {
                rev[i] |= 1 << (ln - 1 - j);
            }
        }
    }
    return rev;
}

void FFT(Complex* a, size_t n, std::vector<size_t> rev, bool direction) {

    for (size_t i = 0; i < n; ++i) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }

    for (size_t len = 2; len <= n; len <<= 1) {
        double alpha = 2 * M_PI / static_cast<double>(len) * (direction ? -1 : 1);
        size_t half_len = len >> 1;

        Complex wlen(cos(alpha), sin(alpha));
        std::vector<Complex> pows;
        pows.emplace_back(1);
        for (size_t i = 1; i < half_len; ++i) {
            pows.emplace_back(pows[i - 1] * wlen);
        }

        for (size_t i = 0; i < n; i += len) {
            Complex t = 0;
            
            for (Complex *pu = a + i, *pv = a + i + half_len, *pw = &*pows.begin(); pu !=  a + i + half_len; ++pu, ++pv, ++pw) {
                t = *pv * *pw;
                *pv = *pu - t;
                *pu += t;
            }
        }
    }

    if (direction) {
        for (size_t i = 0; i < n; ++i) {
            a[i] /= static_cast<double>(n);
        }
    }
}

std::vector<int64_t> Mul(std::vector<int64_t>& a, std::vector<int64_t>& b) {
    size_t n = a.size();
    size_t m = b.size();
    size_t size = 1;
    size_t max = std::max(n, m);
    while (size < max) {
        size <<= 1;
    }
    size <<= 1;

    auto fa = new Complex[size];
    auto fb = new Complex[size];

    for (size_t i = 0; i < a.size(); ++i) {
        fa[i] = Complex(static_cast<double>(a[i]), 0);
    }
    for (size_t i = 0; i < b.size(); ++i) {
        fb[i] = Complex(static_cast<double>(b[i]), 0);
    }

    std::vector<size_t> rev = PrecalcRev(size, static_cast<size_t>(std::log2(size)));
    
    FFT(fa, size, rev, false), FFT(fb, size, rev, false);
    for (size_t i = 0; i < size; ++i) {
        fa[i] *= fb[i];
    }
    delete[] fb;
    FFT(fa, size, rev, true);
    auto answer_size = a.size() + b.size() - 2;
    std::vector<int64_t> answer(answer_size + 1);
    for (size_t i = 0; i <= answer_size; ++i) {
        double delta = fa[i].real() >= 0 ? 0.5 : -0.5;
        answer[i] = static_cast<int64_t>(fa[i].real() + delta);
    }
    delete[] fa;
    
    return answer;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<int64_t> a(n + 1);
    for (size_t i = 0; i <= n; ++i) {
        std::cin >> a[i];
    }
    std::reverse(a.begin(), a.end());

    size_t m = 0;
    std::cin >> m;
    std::vector<int64_t> b(m + 1);
    for (size_t i = 0; i <= m; ++i) {
        std::cin >> b[i];
    }
    std::reverse(b.begin(), b.end());
    std::vector<int64_t> answer;
    answer = Mul(a, b);
    std::cout << answer.size() - 1 << " ";
    for (int i = static_cast<int>(answer.size()) - 1; i >= 0; --i) {
        std::cout << answer[i] << " ";
    }
    return 0;
}