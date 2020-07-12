void pre(int n) //筛选n以内的素数
{
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            isPrime[++cnt] = i;
        for (int j = 1; j <= cnt && i * isPrime[j] <= n; j++)
        {
            vis[i * isPrime[j]] = 1;
            if (i % isPrime[j] == 0)
                break;
        }
    }
}
bool isPrime_3(int num) //判断该数是否为素数
{
    if (num == 2 || num == 3)
        return 1;
    if (num % 6 != 1 && num % 6 != 5)
        return 0;
    int tmp = sqrt(num);
    for (int i = 5; i <= tmp; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    return 1;
}