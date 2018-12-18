#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
#define int unsigned int
const int N = 20000010;
const int inf = 0x3f3f3f3f;
namespace GenHelper
{
unsigned z1, z2, z3, z4, b;
unsigned rand_()
{
    b = ((z1 << 6) ^ z1) >> 13;
    z1 = ((z1 & 4294967294U) << 18) ^ b;
    b = ((z2 << 2) ^ z2) >> 27;
    z2 = ((z2 & 4294967288U) << 2) ^ b;
    b = ((z3 << 13) ^ z3) >> 21;
    z3 = ((z3 & 4294967280U) << 7) ^ b;
    b = ((z4 << 3) ^ z4) >> 12;
    z4 = ((z4 & 4294967168U) << 13) ^ b;
    return (z1 ^ z2 ^ z3 ^ z4);
}
} // namespace GenHelper
void srand(unsigned x)
{
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
}
int read()
{
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}
ll ans;
int n, m, s;
int a[N];
int pre[N], suf[N];
int blk, bel[N];
int mx[5000][20];
int Log[5000];
signed main()
{
    cin >> n >> m >> s;
    srand(s);
    for (int i = 1; i <= n; i++)
        a[i] = read();
    blk = pow(n, 0.53);
    for (int i = 1; i <= n; i++)
        bel[i] = (i - 1) / blk + 1, mx[bel[i]][0] = max(mx[bel[i]][0], a[i]);
    for (int i = 2; i <= bel[n]; i++)
        Log[i] = Log[i >> 1] + 1;
    for (int k = 1; (1 << k) <= bel[n]; k++)
    {
        for (int i = 1; i + (1 << (k - 1)) - 1 <= bel[n]; i++)
            mx[i][k] = max(mx[i][k - 1], mx[i + (1 << (k - 1))][k - 1]);
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        if (bel[i] != bel[i - 1])
            res = 0;
        res = max(res, a[i]);
        pre[i] = res;
    }
    for (int i = n; i >= 1; i--)
    {
        if (bel[i] != bel[i + 1])
            res = 0;
        res = max(res, a[i]);
        suf[i] = res;
    }
    for (int i = 1; i <= m; i++)
    {
        int l = read() % n + 1, r = read() % n + 1;
        if (l > r)
            swap(l, r);
        int res = 0;
        if ((l - 1) / blk == (r - 1) / blk)
        {
            for (int j = l; j <= r; j++)
                res = max(res, a[j]);
        }
        else
        {
            res = max(pre[r], suf[l]);
            int tl = (l - 1) / blk + 2, tr = (r - 1) / blk;
            if (tl <= tr)
            {
                int k = Log[tr - tl + 1];
                res = max(res, max(mx[tl][k], mx[tr - (1 << k) + 1][k]));
            }
        }
        ans += res;
    }
    cout << ans << endl;
    return 0;
}