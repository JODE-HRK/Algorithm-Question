#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#define pii pair<int, int>
using namespace std;
int t, head;
int maxx = -110, maxy = -110, minx = 110, miny = 110, x, y;
bool p[110][110];
queue<pii> Q;
string str;
void move()
{
    if (head == 0)
        x--;
    else if (head == 1)
        y++;
    else if (head == 2)
        x++;
    else
        y--;
    // p[x][y] = true;
    maxx = max(maxx, x);
    maxy = max(maxy, y);
    minx = min(maxx, x);
    miny = min(maxy, y);
    Q.push(pii(x, y));
}
void forward()
{
    move();
}
void turnright()
{
    head = (head + 1) % 4;
    move();
}
void turnleft()
{
    head = (head + 4 - 1) % 4;
    move();
}
void back()
{
    head = head - 2 >= 0 ? head - 2 : head + 2;
    move();
}
void update1()
{
    maxx = -110, maxy = -110, minx = 110, miny = 110;
    for (int i = 0; i < str.length(); i++)
    {
        // cout << str[i];
        // cout << str[i] << endl;
        if (str[i] == 'F')
            forward();
        else if (str[i] == 'R')
            turnright();
        else if (str[i] == 'L')
            turnleft();
        else
            back();
    }
    // cout << endl;
}
int main()
{
    cin >> t;
    cout << t << endl;
    while (t--)
    {
        memset(p, 0, sizeof(p));
        x = 0, y = 0;
        Q.push(pii(x, y));
        p[x][y] = true;
        head = 1;
        cin >> str;
        update1();
        cout << maxx - minx + 3 << ' ' << maxy - miny + 2 << endl;
        while (!Q.empty())
        {
            pii now = Q.front();
            p[now.first + abs(minx) + 1][now.second + abs(miny)] = true;
            Q.pop();
        }
        for (int i = 0; i < maxx - minx + 3; i++)
        {
            for (int j = 0; j < maxy - miny + 2; j++)
                if (p[i][j] == true)
                    cout << '.';
                else
                    cout << '#';
            cout << endl;
        }
    }
    return 0;
}