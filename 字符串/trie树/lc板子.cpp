#include <bits/stdc++.h>
using namespace std;

struct trie {
    const int maxsize = 5e5 + 7; // reserve大小; 更大的话会push_back
    // vector<map<int, int>> tree;
    vector<array<int, 26>> tree;
    trie() {
        // tree.reserve(maxsize);
        clear();
    }
    int newnode() {
        tree.push_back({});
        return tree.size() - 1;
    }
    vector<int> insert(const string &s, int id) {
        int root = 0;
        vector<int> ret(1, 0);
        for (char c : s) {
            int x = c - 'a';
            if (!tree[root][x])
                tree[root][x] = newnode();
            // printf("root %d x=%d: %d\n",root,x,tree[root][x]);
            root = tree[root][x];
            ret.push_back(root);
        }
        return ret;
    }
    vector<int> query(const string &s) {
        int root = 0;
        vector<int> ret(1, 0);
        for (char c : s) {
            int x = c - 'a';
            // printf("root %d x=%d: %d\n",root,x,tree[root][x]);
            if (!tree[root][x])
                break;
            root = tree[root][x];
            ret.push_back(root);
        }
        return ret;
    }
    void clear() {
        tree.clear();
        newnode();
    }
} tree;
class Solution {
  public:
    const int INF = 1e9 + 7;
    vector<int> stringIndices(vector<string> &wordsContainer, vector<string> &wordsQuery) {
        tree.clear();
        vector<pair<int, int>> P;
        for (int i = 0; i < wordsContainer.size(); i++) {
            string &cur = wordsContainer[i];
            reverse(cur.begin(), cur.end());
            auto vec = tree.insert(cur, i);
            P.resize(max((int)P.size(), vec.back() + 1), {INF, INF});
            // for (int v:vec) printf("%d ",v); puts("");
            for (int v : vec)
                P[v] = min(P[v], {cur.size(), i});
        }
        vector<int> ret;
        for (int i = 0; i < wordsQuery.size(); i++) {
            string &cur = wordsQuery[i];
            reverse(cur.begin(), cur.end());
            auto vec = tree.query(cur);
            // for (int v:vec) printf("%d(%d %d) ",v); puts(" Q");
            ret.push_back(P[vec.back()].second);
        }
        return ret;
    }
};