#include <bits/stdc++.h>
using namespace std;
string str;
char st[10000001];
int main()
{
    cin >> str;
    transform(str.begin(), str.end(), str.begin(), ::toupper); //转换成大写
    // transform(str.begin(), str.end(), str.end(), ::tolower);//转换成小写
    //toupper(str[i]),tolower(str[i]); //为单个字符转换，string和字符数组都有效
    cout << str;
    return 0;
}