//
// Created by JODE on 2023-01-27.
//
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> ans;
        unordered_set<string> dict(words.begin(), words.end());
        for (auto word: words){
            int len = word.length();
//            printf("%d\n", len);
            vector<bool> dp(len + 1);
            dp[0] = true;
            for (int i = 1; i <= len; ++i) {
                for (int j = (i == len ? 1 : 0); !dp[i] && j < i; ++j) {
                    dp[i] = dp[j] && dict.count(word.substr(j, i - j));
                }
            }
            if (dp[len])
                ans.push_back(word);
        }
        return ans;
    }
};