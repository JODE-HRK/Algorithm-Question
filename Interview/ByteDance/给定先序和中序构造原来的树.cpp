/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-10-28 10:13:02
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-10-28 10:22:26
 * 给定先序遍历和中序遍历，构造原来的树
 */
#include <bits/stdc++.h>
using namespace std;

int preorder[5] = {3, 9, 20, 15, 7};
int inorder[5] = {9, 3, 15, 20, 7};
int rootcnt = 0;
int len = 4;
int lel;
int tree[101];
void dfs(int id, int l, int r)
{
    lel = max(lel, id);
    int root = preorder[rootcnt];
    tree[id] = preorder[rootcnt];
    ++rootcnt;
    if (l == r)
        return;
    int mid;
    for (int i = l; i <= r; i++)
        if (inorder[i] == tree[id])
        {
            mid = i;
            break;
        }
    dfs(id << 1, l, mid - 1);
    dfs(id << 1 | 1, mid + 1, r);
}
int main()
{
    dfs(1, 0, 4);
    for (int i = 1; i <= lel; i++)
        printf("%d ", tree[i]);
    return 0;
}