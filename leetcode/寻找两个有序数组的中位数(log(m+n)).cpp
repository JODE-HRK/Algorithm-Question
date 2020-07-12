#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int n, m;
        auto a = nums1;
        auto b = nums2;
        m = a.size();
        n = b.size();
        if (m > n)
        {
            swap(a, b);
            swap(n, m);
        }
        int l = 0, r = m, pos, half = (n + m + 1) >> 1;
        while (l <= r)
        {
            cout << l << ' ' << r << endl;
            int i = (l + r) >> 1, j = half - i;
            cout << "i:" << i << endl
                 << "j:" << j << endl;
            if (i < r && b[j - 1] > a[i])
                l = i + 1;
            else if (i > l && a[i - 1] > b[j])
                r = i - 1;
            else
            {
                int maxleft, minright;
                if (i == 0)
                    maxleft = b[j - 1];
                else if (j == 0)
                    maxleft = a[i - 1];
                else
                    maxleft = max(a[i - 1], b[j - 1]);
                if ((n + m) % 2)
                    return maxleft;
                if (i == m)
                    minright = b[j];
                else if (j == n)
                    minright = a[i];
                else
                    minright = min(a[i], b[j]);
                return (1.0 * maxleft + 1.0 * minright) / 2.0;
            }
        }
        return 1;
    }
};