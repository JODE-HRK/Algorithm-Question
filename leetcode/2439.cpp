//
// Created by JODE on 2023-04-05.
//
class Solution {
public:
    int minimizeArrayValue(vector<int>& nums) {
        int cnt = 1, sum = 1e9+1, ans = 0, last = 1e9+1;
        bool start = false;
        for(auto x: nums){
            if(x < last){
                cout<< x << " "<< last << " "<< cnt << endl;
                if(start){
                    if (sum % cnt == 0)
                        ans = max(ans, sum / cnt);
                    else
                        ans = max(ans, sum / cnt + 1);
                }
                cnt = 0, sum = 0;
                start = true;
            }
            cnt += 1;
            sum += x;
            last = x;
        }
        if (cnt != 0){
            if (sum % cnt == 0)
                ans = max(ans, sum / cnt);
            else
                ans = max(ans, sum / cnt + 1);
        }
        return ans;
    }
};