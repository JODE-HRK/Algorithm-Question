//
// Created by JODE on 2023-01-28.
//
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class SummaryRanges {
private:
    vector<int> Nums;
    vector<vector<int>> intervals;
public:
    SummaryRanges() {
        Nums.clear();
        intervals.clear();
    }

    void addNum(int value) {
        int pos = lower_bound(Nums.begin(), Nums.end(), value) - Nums.begin();
        Nums.insert(Nums.begin() + pos, value);
        vector<int> newInterval;
        newInterval.push_back(value);
        newInterval.push_back(value);
        if (intervals.size() == 0){
            intervals.push_back(newInterval);
            return;
        }
        int index = lower_bound(intervals.begin(), intervals.end(), newInterval) - intervals.begin();
        printf("Index: %d\n", index);
        if (index == intervals.size()) {
            if (intervals[index - 1][1] + 1 >= newInterval[0])
                intervals[index - 1][1] = max(newInterval[1], intervals[index - 1][1]);
            else{
                intervals.push_back(newInterval);
            }
            return;
        }
        if (intervals[index][0] <= newInterval[0] && newInterval[1] <= intervals[index][1])
            return;
        if (index == 0) {
            if (intervals[index][0] == newInterval[1] + 1)
                intervals[index][0] = min(newInterval[0], intervals[index][0]);
            else
                intervals.insert(intervals.begin() + index, newInterval);
        }
        else{
            if (intervals[index - 1][0] <= newInterval[0] && newInterval[1] <= intervals[index - 1][1])
                return;
            if (intervals[index-1][1] >= newInterval[0] - 1 && intervals[index][0] <= newInterval[1] + 1){
                intervals[index][0] = intervals[index - 1][0];
                intervals.erase(intervals.begin() + index - 1);
            }
            else if (intervals[index][0] == newInterval[1] + 1)
                intervals[index][0] = newInterval[0];
            else if (intervals[index - 1][1] == newInterval[0] - 1)
                intervals[index - 1][1] = newInterval[1];
            else
                intervals.insert(intervals.begin() + index, newInterval);
        }

        printf("Add: %d\n", value);
        for (auto interval: intervals){
            cout<< interval[0] << ' ' << interval[1] << endl;
        }
    }

    vector<vector<int>> getIntervals() {
        return intervals;
    }
};