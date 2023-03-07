//
// Created by JODE on 2023-03-07.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:

    bool judge(vector<int>& time, int totalTrips, long long t) {
        long long tmp = 0;
        for( auto x: time){
            tmp += t / x;
        }
        if (tmp >= totalTrips)
            return true;
        return false;
    }

    long long minimumTime(vector<int>& time, int totalTrips) {
        sort(time.begin(), time.end());
        long long maxTime = (long long) totalTrips * time.front();
        long long l = 0, r = maxTime, ans;

        while (l <= r){
            long long mid = (l + r) >> 1;
            cout<<l<<" "<<r<<" "<<mid<<endl;
            if (judge(time, totalTrips, mid)){
                ans = mid;
                r = mid - 1;
            }
            else
                l =  mid + 1;
        }

        return ans;
    }
};