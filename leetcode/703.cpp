//
// Created by JODE on 2023-05-23.
//
#include "queue"
using namespace std;
class KthLargest {
private:
    priority_queue<int, vector<int>,greater<int> > Q;
    int K;
public:
    KthLargest(int k, vector<int>& nums) {

        K = k;
        while (!Q.empty())
            Q.pop();
        for (auto x: nums){
            Q.push(x);
        }
        while (Q.size() > k){
//            printf("%d", Q.top());
            Q.pop();
        }
    }

    int add(int val) {
        if(Q.size() < K){
            Q.push(val);
            return Q.top();
        }
        if (val <= Q.top())
            return Q.top();
        else{
            Q.push(val);
//            printf("%d", Q.top());
            Q.pop();
        }
        return Q.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */