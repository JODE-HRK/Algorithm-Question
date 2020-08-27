#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
const int maxn = 1e5 + 7;
char str[maxn];
int sum[10][2];
int pa9[10];
int least[10][2];
vector<pii> G, S;
stack<int> Q1, Q2;
void print()
{
    while (least[0][0] > 0 && least[0][1] > 0)
        Q1.push(0), Q2.push(0), least[0][1]--, least[0][0]--;
    if (!G.empty())
    {
        // printf("%d %d\n", G[0].first, G[0].second);
        Q1.push(G[0].first);
        Q2.push(G[0].second);
    }
    for (int i = 0; i < 10; i++)
    {
        while (pa9[i] > 0)
        {
            Q1.push(i);
            Q2.push(9 - i);
            pa9[i]--;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        while (least[i][0] > 0)
            Q1.push(i), least[i][0]--;
        while (least[i][1] > 0)
            Q2.push(i), least[i][1]--;
    }
    while (!Q1.empty())
        printf("%d", Q1.top()), Q1.pop();
    cout << endl;
    while (!Q2.empty())
        printf("%d", Q2.top()), Q2.pop();
}
int main()
{
    memset(sum, 0, sizeof(sum));
    memset(pa9, 0, sizeof(pa9));
    memset(least, 0, sizeof(least));
    scanf("%s", str);
    int l = strlen(str);
    // printf("%d\n", l);
    for (int i = 0; i < l; i++)
    {
        int id = str[i] - '0';
        sum[id][0]++, sum[id][1]++;
    }
    for (int i = 0; i < 5; i++)
        if (sum[i][0] > 0 && sum[9 - i][1] > 0)
            pa9[9 - i] = pa9[i] = min(sum[i][0], sum[9 - i][1]);
    // for (int i = 0; i < 10; i++)
    //     printf("%d ", pa9[i]);
    // cout << endl;
    for (int i = 0; i < 10; i++)
        least[i][1] = least[i][0] = max(0, sum[i][0] - pa9[i]);
    for (int i = 1; i < 10; i++)
        if (least[i][0] > 0 && least[10 - i][1] > 0)
        {
            G.push_back(make_pair(i, 10 - i)), least[i][0]--, least[10 - i][1]--;
            break;
        }
    // for (int i = 0; i < 10; i++)
    //     printf("i:%d 1:%d 2:%d\n", i, least[i][0], least[i][1]);
    // cout << endl;
    if (G.empty())
    {
        // printf("1\n");
        for (int i = 1; i < 10; i++)
            if (least[i][0] > 0 && pa9[10 - i] > 0)
            {
                // printf("%d %d\n", i, 10 - i);
                G.push_back(make_pair(i, 10 - i));
                // pa9[10 - i]--;
                pa9[i - 1]--;
                least[i - 1][0]++;
                least[i][0]--;
                break;
            }
    }
    // for (int i = 0; i < 10; i++)
    //     printf("i:%d 1:%d 2:%d\n", i, least[i][0], least[i][1]);
    // cout << endl;
    // for (int i = 0; i < 10; i++)
    //     printf("%d ", pa9[i]);
    // cout << endl;
    if (G.empty())
    {
        for (int i = 1; i < 10; i++)
        {
            if (pa9[i] > 0 && pa9[10 - i] > 0)
            {
                printf("2\n");
                G.push_back(make_pair(i, 10 - i));
                // pa9[i]--, pa9[10 - i]--;
                pa9[i]--, pa9[i - 1]--;
                least[9 - i][1]++, least[i - 1][0]++;
                break;
            }
        }
    }
    // for (int i = 0; i < 10; i++)
    //     printf("i:%d 1:%d 2:%d\n", i, least[i][0], least[i][1]);
    // cout << endl;
    // for (int i = 0; i < 10; i++)
    //     printf("%d ", pa9[i]);
    // cout << endl;
    print();
    return 0;
}