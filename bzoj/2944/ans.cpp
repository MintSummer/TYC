 
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
namespace zyt
{
    typedef long long ll;
    ll Catalan[20];
    void dfs(ll n, int k, int tmp)
    {
        int sizel = 0, sizer = k - 1;
        while (n)
        {
            if (n > Catalan[sizel] * Catalan[sizer])
            {
                n -= Catalan[sizel] * Catalan[sizer];
                sizel++, sizer--;
            }
            else
                break;
        }
        printf("%c", (char)(sizel + tmp + 'a'));
        if (sizel > 0)
            dfs(ceil((double)n / Catalan[sizer]), sizel, tmp);
        if (sizer > 0)
        {
            int x = n % Catalan[sizer];
            dfs(x ? x : Catalan[sizer], sizer, tmp + sizel + 1);
        }
    }
    void work()
    {
        ll n;
        int k;
        scanf("%lld%d", &n, &k);
        Catalan[0] = 1;
        for (int i = 1; i <= k; i++)
            Catalan[i] = Catalan[i - 1] * (4 * i - 2) / (i + 1);
        dfs(n, k, 0);
    }
}
int main()
{
    zyt::work();
    return 0;
}
﻿
