#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int t, id, n;
char str[10];
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &id);
        scanf("%s", str);
        int Octa = -1, Dec = 0, hex = 0;
        char *stop = NULL;
        Octa = strtol(str, &stop, 8);
        if (*stop != '\n' && *stop != '\000')
            Octa = 0;
        Dec = strtol(str, &stop, 10);
        hex = strtol(str, &stop, 16);
        printf("%d %d %d %d\n", id, Octa, Dec, hex);
    }
    return 0;
}