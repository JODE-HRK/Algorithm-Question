#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack <int> Q;
        vector<int> ans;
        int l=nums.size(),maxx = -10000000,maxn=nums[0];
        for(int i=0;i<l;i++)
            maxn = max(nums[i],maxn);
        for(int i=0;i<2*l;i++){
            if(Q.empty() || Q.top()>=nums[i])
                Q.push(nums[i]),maxx = max(maxx,nums[i]);
            else {
                while(Q.top()<nums[i]){
                    Q.pop(),ans.push_back(nums[i]);
                    // while(!Q.empty() && Q.top()==maxn){
                    //     ans.push_back(-1),Q.pop();
                    //     if(ans.size()==l)
                    //         return ans;
                    // }
                    if(ans.size()==l)
                            return ans;
                    if(Q.empty())
                        maxx = -10000000;
                }
                Q.push(nums[i]);
                maxx = nums[i];
            }
        }
        return ans;
    }
};