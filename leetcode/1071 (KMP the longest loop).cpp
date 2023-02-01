//
// Created by JODE on 2023-02-01.
//
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <string>
using namespace std;
class Solution {
private:
    int getNxt(string &str){
        int j,k;
        int len = str.size();
        int nxt[len + 1];
        j = 0, nxt[0] = -1, k = -1;
        while (j < len){
            if (k == -1 || str[j] == str[k]){
                j++, k++;
                nxt[j] = k;
            }
            else
                k = nxt[k];
        }
        return len - nxt[len];
    }
    bool judge(string mode, string str){
        int st = 0, len = mode.size();
//        printf("%s\n", mode.c_str());
        while (st < str.size()){
            if (str.substr(st, len) == mode)
                st += len;
            else
                return false;
        }
        return true;
    }
public:
    string gcdOfStrings(string str1, string str2) {
        int len1 = str1.size(), len2 = str2.size();
        int loop1len = getNxt(str1);
        string loop1;
        if (loop1len !=0 && len1 % loop1len == 0)
            loop1 = str1.substr(0, loop1len);
        else
            loop1 = str1;
        int loop2len = getNxt(str2);
        string loop2;
        if (loop2len !=0 && len2 % loop2len == 0)
            loop2 = str2.substr(0, loop2len);
        else
            loop2 = str2;
        string ansstr = "";
        if (loop1 == loop2){
            ansstr = loop1;
            string singleStr= ansstr;
            int lenLoop = ansstr.size();
            string tmpStr = singleStr;
            lenLoop += singleStr.size();
            tmpStr += singleStr;
//            printf("%s %d\n", tmpStr.c_str(), lenLoop);
            while (lenLoop <= min(len1, len2)){
//                printf("%s %d\n", tmpStr.c_str(), lenLoop);
                if (len1 % lenLoop !=0 || len2 % lenLoop != 0){
                    tmpStr += singleStr;
                    lenLoop += singleStr.size();
                    continue;
                }
                if (judge(tmpStr, str1) && judge(tmpStr, str2))
                    ansstr = tmpStr;
                tmpStr += singleStr;
                lenLoop += singleStr.size();
            }
        }
        return ansstr;
    }
};