// O(n) solution

#include <iostream>
#include <map>
#include <vector>
struct Vertex {
    Vertex() = default;
    Vertex(int l, int r, int p) : left(l), right(r), parent(p) {
    }
    int left = -1;
    int right = -1;
    int parent = -1;
    int link = 0;
    std::map<char, int> next;
};
void DFS(std::vector<Vertex>& tree, int v_num, size_t& counter, std::vector<size_t>& counters, std::vector<bool>& used,
         size_t& f_len) {
    used[v_num] = true;
    if (v_num != 0) {
        counters[v_num] = counter++;
        std::cout << counters[tree[v_num].parent] << " ";
        if (tree[v_num].left < static_cast<int>(f_len)) {
            std::cout << "0 ";
            std::cout << tree[v_num].left << " ";
            std::cout << (tree[v_num].right < static_cast<int>(f_len) ? tree[v_num].right + 1 : f_len) << "\n";
        } else {
            std::cout << "1 ";
            std::cout << tree[v_num].left - f_len << " ";
            std::cout << (tree[v_num].right - f_len + 1) << "\n";
        }
    }

    for (auto elem : tree[v_num].next) {
        if (!used[elem.second]) {
            DFS(tree, elem.second, counter, counters, used, f_len);
        }
    }
}

class SuffixTree {
public:
    SuffixTree(const std::string& source, size_t f_len)
        : str_(source), cur_vertex_(0), pos_(0), size_(2), cur_pos_(0), f_len_(f_len) {
        tree_.resize(2 * str_.length());
        Vertex root;
        tree_[0] = root;
        Build();
    }
    void Build() {
        tree_[0].link = 1;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            tree_[1].next[ch] = 0;
        }
        tree_[1].next['$'] = 0;
        tree_[1].next['#'] = 0;
        for (size_t i = 2; i < tree_.size(); i++) {
            tree_[i].right = static_cast<int>(str_.length()) - 1;
        }
        for (size_t i = 0; i < str_.length(); i++) {
            Add(str_[i]);
            cur_pos_++;
        }
    }
    void Add(char ch) {
        int flag = 1;
        while (flag == 1) {
            flag = 0;
            int v = cur_vertex_;
            if (tree_[v].right < pos_) {
                if (tree_[v].next.find(ch) == tree_[v].next.end()) {
                    tree_[v].next[ch] = size_;
                    tree_[size_].left = cur_pos_;
                    tree_[size_++].parent = v;
                    v = cur_vertex_ = tree_[v].link;
                    pos_ = tree_[v].right + 1;
                    flag = 1;
                    continue;
                }
                v = cur_vertex_ = tree_[v].next[ch];
                pos_ = tree_[cur_vertex_].left;
            }

            if (pos_ == -1 || ch == str_[pos_]) {
                ++pos_;
            } else {
                tree_[size_] = Vertex(tree_[v].left, pos_ - 1, tree_[v].parent);
                tree_[size_].next[str_[pos_]] = v;

                tree_[size_].next[ch] = size_ + 1;
                tree_[size_ + 1].parent = size_;
                tree_[size_ + 1].left = cur_pos_;

                tree_[v].parent = size_;
                tree_[v].left = pos_;

                tree_[tree_[size_].parent].next[str_[tree_[size_].left]] = size_;

                v = cur_vertex_ = tree_[tree_[size_].parent].link;
                pos_ = tree_[size_].left;

                while (pos_ <= tree_[size_].right) {
                    v = cur_vertex_ = tree_[cur_vertex_].next[str_[pos_]];
                    pos_ += 1 + tree_[cur_vertex_].right - tree_[cur_vertex_].left;
                }

                if (pos_ != tree_[size_].right + 1) {
                    tree_[size_].link = size_ + 2;
                } else {
                    tree_[size_].link = v;
                }
                pos_ = tree_[cur_vertex_].right - pos_ + tree_[size_].right + 2;
                flag = 1;
                size_ += 2;
                continue;
            }
        }
    }
    void Answer() {
        std::vector<size_t> counters(size_, 0);
        std::vector<bool> used(size_, false);
        std::cout << size_ - 1 << "\n";
        size_t counter = 1;
        DFS(tree_, 0, counter, counters, used, f_len_);
    }

private:
    std::string str_;
    std::vector<Vertex> tree_;
    int cur_vertex_;
    int pos_;
    int size_;
    int cur_pos_;
    size_t f_len_;
};

int main() {
    std::string str1;
    std::string str2;

    std::cin >> str1 >> str2;

    std::string str;

    str = str1 + str2;

    SuffixTree suf_tree(str, str1.length());
    suf_tree.Answer();
    return 0;
}