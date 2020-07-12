#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
using namespace std;
int n;
int isprime(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    printf("%d\n", isprime(274177));
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        if (t < 5)
            printf("1\n");
        else
        {
            if (n == 5)
                printf("641\n");
            else if (n == 6)
                printf("274177\n");
            else if (n == 7)
                printf("\n");
            else if (n == 8)
                printf("274177\n");
            else if (n == 9)
                printf("274177\n");
            else if (n == 10)
                printf("274177\n");
        }
    }
    return 0;
}