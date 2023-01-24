//
// Created by JODE on 2023-01-23.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        int sum[n + 1], fa[n + 1];
        for(int i = 1; i <= n; i++)
            sum[i] = 0, fa[i] = -1;
        for(int i = 0; i < trust.size(); i++)
            sum[trust[i][1]]++, fa[trust[i][0]] = trust[i][1];
        for (int i = 1; i <= n ; i++)
            if (sum[i] == n - 1 && fa[i] == -1)
                return i;
        return -1;
    }
};