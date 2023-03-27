#include <iostream>
#include <vector>

int main() {
    std::string str;
    std::string pattern;
    std::cin >> str >> pattern;
    
    std::string newstr;
    newstr =  pattern + '#' + str;
    std::size_t len_s = newstr.size();
    std::size_t len_p = pattern.size();
    std::vector<size_t> prefix(len_s, 0);
    for (size_t i = 1; i < len_s; ++i) {
        size_t value_of_i = prefix[i - 1];
        while (value_of_i > 0 && newstr[i] != newstr[value_of_i]) { 
            value_of_i = prefix[value_of_i - 1];
        }
        if (newstr[i] == newstr[value_of_i]){
            value_of_i++;
        }
        prefix[i] = value_of_i;
    
        if (value_of_i == len_p) {
            std::cout << i - 2 * value_of_i << "\n";
        }
    }
    return 0;
}