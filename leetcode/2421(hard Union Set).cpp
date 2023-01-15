//
// Created by JODE on 2023-01-15.
//
#include <vector>
#include <map>
#include <unordered_map>
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
};

class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        UnionFind uf(n);
        int ans = 0;
        vector<vector<int>> adj(n);
        for (auto& edge: edges){
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        map<int, vector<int>> valueToNodes;
        for (int node = 0; node < n; ++node) {
            valueToNodes[vals[node]].push_back(node);
        }

        for(auto& [value, nodes] : valueToNodes){
            for (int node: nodes) {
                for (int neighbor: adj[node]){
                    if (vals[node] >= vals[neighbor])
                        uf.addNode(node, neighbor);
                }
            }
            unordered_map<int, int> numOfGroup;
            for (int u: nodes){
                numOfGroup[uf.find(u)]++;
            }
            for (auto& [_, num] : numOfGroup) {
                ans += (num * (num + 1) / 2);
            }
        }
        return ans;
    }
};