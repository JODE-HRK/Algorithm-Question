//
// Created by JODE on 2023-03-21.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long cnt = 0, ans = 0;
        for (auto x: nums){
            if (x == 0)
                cnt += 1;
            else{
                ans = (1 + cnt) * cnt / 2;
                cnt = 0;
            }
        }
        return ans;
    }
};