#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
struct op
{
    int width, height;
} a[maxn];
int f[maxn];
int ans = 0, n;
bool cmp(op x, op y)
{
    return x.width > y.width;
}
void getans()
{
    for (int i = 1; i <= n; i++)
    {
        if (a[i].height > f[ans])
            f[++ans] = a[i].height;
        else
        {
            int l = 1, r = ans;
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (f[mid] >= a[i].height)
                    r = mid;
                else
                    l = mid + 1;
            }
            f[l] = a[i].height;
        }
    }
}
int main()
{
    // freopen(".in", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].width >> a[i].height;
    sort(a + 1, a + 1 + n, cmp);
    getans();
    printf("%d", ans);
    return 0;
}
/*
while(h<d)
			{
				mid=(h+d)>>1;
				if(k[mid]>=a[i])
					h=mid+1;	
				else
					d=mid;	
			}//二分在k数组里找第一个小于a[i]的数
*/