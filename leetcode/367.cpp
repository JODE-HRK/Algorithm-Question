//
// Created by JODE on 2023-05-23.
//
class Solution {
public:
    bool isPerfectSquare(int num) {
        int ans = -1;
        num = (long long) num;
        long long l = 1, r = 65536;
        while (l <= r){
            long long mid = (l + r) >> 1;
//            cout<<mid<<endl;
//            cout<<mid * mid<<endl;
//            cout<<endl;
            if(mid * mid == num)
                return true;
            else if(mid * mid > num){
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        return false;
    }
};