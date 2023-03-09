//
// Created by JODE on 2023-03-08.
//
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class Solution {
public:

    bool judge(long long x, vector<int>& piles, int h){
        int time = 0;
        for (auto num: piles){
            time += num / x + (num % x > 0);
            if (time > h)
                return false;
        }
        return true;
    }

    int minEatingSpeed(vector<int>& piles, int h) {

        long long l = 1, r = 1e18;
        long long mid, ans;
        while(l < r) {
            mid = (l + r) >> 1;
            cout<<l<<" "<<r<<" "<<mid<<endl;
            if(judge(mid, piles, h))
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        return ans;
    }
};