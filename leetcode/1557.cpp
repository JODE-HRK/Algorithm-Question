//
// Created by JODE on 2023-05-18.
//
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        int r[n];
        fill(r, r+n, 0);
        for(auto e: edges){
            ++r[e[1]];
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if(r[i] == 0){
                ans.push_back(i);
            }
        }
        return ans;
    }
};