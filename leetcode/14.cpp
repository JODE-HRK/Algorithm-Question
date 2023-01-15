//
// Created by JODE on 2023-01-14.
//
#include <iostream>
#include <vector>
using namespace std;
string longestCommonPrefix(vector<string>& strs) {
    int cnt = 0, len = 1000000, cntlen = 0, sum = strs.size();
    string ans = "";
    for (int i = 0; i < sum; ++i) {
        if(len > strs[i].size())
            len = strs[i].size();
    }
    while (cntlen < len){
        for (int i = 1; i < sum; ++i) {
            if(strs[i][cntlen] != strs[i-1][cntlen])
                break;
            ++cnt;
        }
        if (cnt != sum - 1)
            break;
        else{
            ans += strs[0][cntlen];
        }
        cnt = 0;
        ++cntlen;
    }
    return ans;
}