//
// Created by JODE on 2023-01-16.
//
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
class Solution {
public:
    bool isOverlap(vector<int> x, vector<int> y){
        return min(x[1], y[1]) - max(x[0], y[0]) >= 0;
    }

    vector<int> mergeIntervals(vector<int> x, vector<int> y){
        return {min(x[0], y[0]), max(x[1], y[1])};
    }

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        int index = upper_bound(intervals.begin(), intervals.end(), newInterval) - intervals.begin();
        if (index != intervals.size()) {
            intervals.insert(intervals.begin() + index, newInterval);
        } else {
            intervals.push_back(newInterval);
        }

        for (int i = 0; i < intervals.size(); i++) {
            vector<int> currInterval = {intervals[i][0], intervals[i][1]};
            while (i < intervals.size() && isOverlap(currInterval, intervals[i])) {
                currInterval = mergeIntervals(currInterval, intervals[i]);
                i++;
            }
            i--;
            ans.push_back(currInterval);
        }
        return ans;
    }
};