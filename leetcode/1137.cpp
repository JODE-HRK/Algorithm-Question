//
// Created by JODE on 2023-01-30.
//
class Solution {
private:
    int a[37];
    void pre(){
        a[0] = 0, a[1] = 1, a[2] = 1;
        for (int i = 3; i < 38; ++i) {
            a[i] = a[i-1] + a[i - 2] + a[i - 3];
        }
    }
public:
    int tribonacci(int n) {
        pre();
        return a[n];
    }
};