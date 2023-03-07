//
// Created by JODE on 2023-03-06.
//
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int cnt = 0, num = 0;
        while(k){
            ++num;
            if(cnt < arr.size())
                if(arr[cnt] == num){
                    cnt++;
                    continue;
                }
            k--;
        }
        return num;
    }
};