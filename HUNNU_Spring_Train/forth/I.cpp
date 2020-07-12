#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;
int n, t;
string str[26] = {"@", "8", "(", "|)", "3", "#", "6", "[-]", "|", "_|", "|<", "1", "[]\\/[]", "[]\\[]", "0", "|D", "(,)", "|Z",
                  "$", "']['", "|_|", "\\/", "\\/\\/", "}{", "'/", "2"};
string s;
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        cin >> s;
        cout << s.length() << endl;
    }
    return 0;
}