class Solution
{
public:
    string convert(string s, int numRows)
    {
        vector<string> str(numRows, ""); //使用int也一样，必须开numRows大小
        int l = s.length();
        int cir = numRows * 2 - 2;
        if (cir == 0)
            return s;
        for (int i = 0; i < l; i += cir)
        {
            int cnt = 0;
            while (cnt < cir && cnt + i < l)
            {
                if (cnt < numRows)
                    str[cnt] += s[i + cnt];
                else
                    str[numRows - 1 - (cnt % numRows + 1)] += s[i + cnt];
                cnt++;
            }
        }
        string ans;
        for (int i = 0; i < numRows; i++)
            ans += str[i];
        return ans;
    }
};