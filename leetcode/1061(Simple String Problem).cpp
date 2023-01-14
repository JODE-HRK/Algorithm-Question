//
// Created by JODE on 2023-01-14.
//
#include <iostream>
using namespace std;
int id[26];
string smallestEquivalentString(string s1, string s2, string baseStr) {
    for (int i = 0; i < 26; ++i) {
        id[i] = i;
    }
    int lenS = s1.size();
    for (int i = 0; i < lenS; ++i) {
        int idA = id[s1[i] - 'a'];
        int idB = id[s2[i] - 'a'];
            for (int j = 0; j < 26; ++j) {
                if (id[j] == idB && idA < idB)
                    id[j] = idA;
                else if (id[j] == idA && idA >idB)
                    id[j] = idB;
            }
    }
    string ans = "";
    for (int i = 0; i < baseStr.size(); ++i) {
        int baseId = baseStr[i] - 'a';
        ans += char(id[baseId] + 'a');
    }
    return ans;
}