//
// Created by JODE on 2023-01-12.
//
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
bool isPalindrome(int x) {
    stringstream stream;
    stream << x;
    string positive;
    stream >> positive;
    string negative;
    negative.assign(positive.rbegin(), positive.rend());
    if (positive == negative)
        return true;
    return false;
}