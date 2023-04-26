//
// Created by JODE on 2023-04-26.
//
class Solution {
public:
    int getData(int x){
        int ans = 0;
        while (x) {
            ans += (x%10);
            x /= 10;
        }
        return ans;
    }
    int addDigits(int num) {
        while (num >= 10){
            num = getData(num);

        }
        return num;
    }
};