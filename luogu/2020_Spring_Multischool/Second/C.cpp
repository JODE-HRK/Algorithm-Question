#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 6;
int n, cnt = 0, m, p = 0, y;
string str[maxn];
string st;
vector<int> stMonth[maxn], endMonth[maxn];
vector<int> week[maxn];
vector<int> stClass[maxn], endClass[maxn];
bool lesson[13];
struct Ans
{
    int sta, ed;
    string name;
};
vector<Ans> ans;
int getsum(int &sst)
{
    int sum = 0;
    for (int i = sst; i < st.length(); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            sst = i + 1;
            return sum;
        }
        sum = sum * 10 + st[i] - '0';
    }
    return sum;
}
int getweek(int sst)
{
    for (int i = sst; i < st.length(); i++)
    {
        if (st[i] == 'M')
            return 1;
        if (st[i] == 'W')
            return 3;
        if (st[i] == 'F')
            return 5;
        if (st[i] == 'u')
            return 2;
        if (st[i] == 'h')
            return 4;
    }
    return 0;
}
bool cmp(Ans x, Ans y)
{
    return x.sta < y.sta;
}
int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d", &n);
    cin.get();
    while (getline(cin, st))
    {
        if ((st[0] >= 'A' && st[0] <= 'Z') || (st[0] >= 'a' && st[0] <= 'z'))
        {
            str[++cnt] = st;
            p = 1;
            str[cnt].erase(str[cnt].end() - 1);
        }
        else
        {
            if (st.find("-") == st.npos)
                break;
            y = 0;
            stMonth[cnt].push_back(getsum(y));
            endMonth[cnt].push_back(getsum(y));
            week[cnt].push_back(getweek(y));
            y += 4;
            stClass[cnt].push_back(getsum(y));
            endClass[cnt].push_back(getsum(y));
            p = 0;
        }
    }

    // for (int i = 1; i <= cnt; i++)
    // {
    // 	cout << str[i] << endl;
    // 	int len = stMonth[i].size();
    // 	for (int j = 0; j < len; j++)
    // 	{
    // 		printf("%d %d %d %d %d\n", stMonth[i][j], endMonth[i][j], week[i][j], stClass[i][j], endClass[i][j]);
    // 	}
    // 	cout << endl;
    // }
    // cout << endl
    // 	 << endl
    // 	 << endl;
    int now = 0;
    m = getsum(now);
    while (m--)
    {
        ans.clear();
        int month, weekday;
        scanf("%d", &month);
        cin >> st;
        weekday = getweek(0);
        for (int i = 1; i <= cnt; i++)
        {
            int len = stMonth[i].size();
            for (int j = 0; j < len; j++)
            {
                if (stMonth[i][j] <= month && month <= endMonth[i][j] && week[i][j] == weekday)
                {
                    ans.push_back({stClass[i][j], endClass[i][j], str[i]});
                }
            }
        }
        sort(ans.begin(), ans.end(), cmp);
        for (int i = 0; i < ans.size(); i++)
        {
            printf("%d-%d ", ans[i].sta, ans[i].ed);
            cout << ans[i].name;
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}