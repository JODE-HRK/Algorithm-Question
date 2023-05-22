//
// Created by JODE on 2023-05-22.
//
class Solution {
private:
    struct Num{
        int val, freq;
    };
    static bool cmpre(Num x,Num y) { return (x.freq > y.freq);}
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int cnt[20007];
        memset(cnt,0,sizeof(cnt));
        vector<Num> V;
        vector<int> ans;
//        V.clear(), ans.clear();
        for(auto x: nums){
            cnt[x+10000]++;
        }
        for (int i = 0; i <= 20000; ++i) {
            if(cnt[i]){
                V.push_back(Num{i-10000, cnt[i]});
            }
        }
        sort(V.begin(), V.end(), cmpre);
        for(int i = 0; i < k; i++){
            ans.push_back(V[i].val);
        }
        return ans;
    }
};