#include <bits/stdc++.h>
using namespace std;
int ans;
char s[1001];
int four = 0, seven = 0;
int main()
{
    scanf("%s", s);
    for (int i = 0; i < strlen(s); i++)
    {
        int id = s[i] - '0';
        if (id == 4)
            four++;
        if (id == 7)
            seven++;
    }
    if (four == 0 && seven == 0)
    {
        printf("-1");
        return 0;
    }
    if (four >= seven)
        printf("4");
    else
        printf("7");
    return 0;
}