#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
struct node
{
    string ddl;
    int ti;
} t;
vector<node> v[1010];
vector<node>::iterator it;
vector<node>::iterator it1;
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int x;
            string ddl;
            int edtime;
            scanf("%d", &x);
            cin >> ddl;
            scanf("%d", &edtime);

            v[x].push_back(node{ddl, edtime});
        }
        else if (op == 2)
        {
            int x;
            scanf("%d", &x);

            int minti = inf;
            string ans = "";
            int flag = 0;

            for (it = v[x].begin(); it != v[x].end(); it++)
            {
                node temp = *it;
                //            	cout<<"ti="<<temp.ti<<" string="<<temp.ddl<<endl;
                if (temp.ti >= i)
                {
                    if (temp.ti < minti)
                    {
                        //            			cout<<"minti="<<minti<<endl;
                        minti = temp.ti;
                        ans = temp.ddl;
                        flag = 1;
                    }
                }
            }
            if (!flag)
                printf("Happy\n");
            else
                cout << ans << endl;
        }
        else if (op == 3)
        {
            int x;
            string s;
            scanf("%d", &x);
            cin >> s;

            int flag = 0;
            for (it1 = v[x].begin(); it1 != v[x].end(); it1++)
            {
                node temp = (*it1);
                if (i > temp.ti)
                    continue;
                if (temp.ddl == s)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                printf("OK\n");
            else
                printf("GG\n");
        }
    }
    return 0;
}