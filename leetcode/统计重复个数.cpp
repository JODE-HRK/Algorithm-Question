const int maxn = 1e6 + 1;
int a[maxn], nt[maxn], nxt[maxn];
class Solution
{
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2)
    {
        map<int, pair<int, int>> S;
        if (n1 == 0)
            return 0;
        int s1cnt = 0, index = 0, s2cnt = 0;
        S.clear();
        pair<int, int> pre_loop;
        pair<int, int> in_loop;
        while (true)
        {
            s1cnt++;
            for (auto ch : s1)
            {
                if (ch == s2[index])
                {
                    index++;
                    if (index == s2.length())
                        s2cnt++, index = 0;
                }
            }
            if (s1cnt == n1)
                return s2cnt / n2;
            if (S.find(index) != S.end())
            {
                pair<int, int> p = S[index];
                int s1cnt_prime = p.first, s2cnt_prime = p.second;
                pre_loop = p;
                in_loop = make_pair(s1cnt - s1cnt_prime, s2cnt - s2cnt_prime);
                break;
            }
            else
                S[index] = make_pair(s1cnt, s2cnt);
        }
        int ans = pre_loop.second + (n1 - pre_loop.first) / in_loop.first * in_loop.second;
        int rest = (n1 - pre_loop.first) % in_loop.first;
        for (int i = 0; i < rest; i++)
            for (auto ch : s1)
            {
                if (ch == s2[index])
                {
                    index++;
                    if (index == s2.length())
                        ans++, index = 0;
                }
            }
        return ans / n2;
    }
};