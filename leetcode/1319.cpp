//
// Created by JODE on 2023-03-23.
//
#include "iostream"
#include "cstdlib"
#include "vector"
#include "cstdio"

using namespace std;
class UnionFind{
private:
    vector<int> fa, rank;
public:
    UnionFind(int size){
        fa.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            fa[i] = i;
        }
    }

    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    // rank optimization, reduce the height of the tree.
    // in this problem, there is no more optimization.
    void addNode(int x, int y){
        int fax = find(x), fay = find(y);
        if (fax == fay)
            return;
        else if (rank[fax] < rank[fay])
            fa[fax] = fay;
        else if (rank[fax] > rank[fay])
            fa[fay] = fax;
        else{
            fa[fay] = fax;
            rank[fax]++;
        }
        return;
    }
    bool judge(int x){
        return fa[x] == x ? 1 : 0;
    }
};
class Solution{
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1)
            return -1;
        UnionFind uf(n);
        for (auto e: connections){
            int x = e[0], y = e[1];
            uf.addNode(x, y);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (uf.judge(i))
                ans += 1;
        }
        return ans - 1;
    }
};
