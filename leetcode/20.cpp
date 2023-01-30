//
// Created by JODE on 2023-01-30.
//
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        stack<char> S;
        for (auto x: s){
            if (x == ']'){
                if (!S.empty() && S.top() == '[')
                    S.pop();
                else
                    return false;
            }
            else if (x == ')'){
                if (!S.empty() && S.top() == '(')
                    S.pop();
                else
                    return false;
            }
            else if (x == '}'){
                if (!S.empty() && S.top() == '{')
                    S.pop();
                else
                    return false;
            }
            else
                S.push(x);
        }
        if (!S.empty())
            return false;
        return true;
    }
};