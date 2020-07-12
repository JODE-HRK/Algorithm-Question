#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool change(int &sum, int tmpx, int tmpy, vector<vector<char>> &board)
    {
        if (board[tmpx][tmpy] == 'B')
            return 1;
        if (board[tmpx][tmpy] == 'p')
        {
            ++sum;
            return 1;
        }
        return 0;
    }
    int numRookCaptures(vector<vector<char>> &board)
    {
        int l = board[0].size(), x, y;
        for (int i = 0; i < l; i++)
            for (int j = 0; j < l; j++)
                if (board[i][j] == 'R')
                    x = i, y = j;
        int sum = 0, tmpx, tmpy;
        tmpx = x, tmpy = y;
        while (tmpx > 0)
        {
            --tmpx;
            if (change(sum, tmpx, tmpy, board))
                break;
        }
        tmpx = x;
        while (tmpy > 0)
        {
            --tmpy;
            if (change(sum, tmpx, tmpy, board))
                break;
        }
        tmpy = y;
        while (tmpx < l)
        {
            ++tmpx;
            if (change(sum, tmpx, tmpy, board))
                break;
        }
        tmpx = x;
        while (tmpy < l)
        {
            ++tmpy;
            if (change(sum, tmpx, tmpy, board))
                break;
        }
        return sum;
    }
};