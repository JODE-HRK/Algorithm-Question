#include <bits/stdc++.h>
using namespace std;
int evalRPN(vector<string> &tokens)
{
    stack<int> Q;
    for (auto t : tokens)
    {
        char v = t[0];
        if (t.length() == 1 && (v == '*' || v == '+' || v == '-' || v == '/'))
        {
            int y = Q.top();
            Q.pop();
            int x = Q.top();
            Q.pop();
            if (v == '*')
                Q.push(x * y);
            else if (v == '/')
                Q.push(x / y);
            else if (v == '+')
                Q.push(x + y);
            else
                Q.push(x - y);
            continue;
        }
        int sum = 0, p = 1;
        for (auto x : t)
            if (x >= '0' && x <= '9')
                sum = sum * 10 + x - '0';
            else if(x=='-')
                p = -1;
        // cout << p*sum << endl;
        Q.push(p*sum);
    }
    return Q.top();
}
vector<string> V;
string s;
int main()
{
    //freopen("1.in", "r", stdin);
    for (int i = 1; i <= 5; i++)
    {
        cin >> s;
        V.push_back(s);
    }
    printf("%d", evalRPN(V));
    return 0;
}