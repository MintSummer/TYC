#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N = 1e5 + 10;
    const ll inf = (1LL << 60);
    int n, len, cnt, tot, L, R, Head[N], dep[N], fa[N], diameter[N], dec[N], add[N], maxx[N];
    ll dis[N], mx[N];
    bool mark[N];

    inline ll Abs(ll x) {return x<0?-x:x;}

    inline int read()
    {
        int x = 0, f = 0; char ch = getchar();
        while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
        return f ? -x : x;
    }

    inline void init()
    {
        tot = cnt = 0;
        memset(mx, 0, sizeof(ll[n+1]));
        memset(dis, 0, sizeof(ll[n+1]));
        memset(maxx, 0, sizeof(ll[n+1]));
        memset(Head, 0, sizeof(int[n+1]));
        memset(mark, 0, sizeof(bool[n+1]));
    }

    struct edge
    {
        int to, next, w;
    }E[N << 1];

    inline void insert(int u, int v, int w)
    {
        E[++cnt] = (edge){v, Head[u], w};
        Head[u] = cnt;
    }

    void dfs(int u, int f)
    { 
        fa[u] = f, dep[u] = dep[f] + 1;
        for (int i = Head[u]; i; i = E[i].next)
        {
            int v = E[i].to;
            if (v == f) continue;
            dis[v] = dis[u] + E[i].w;
            dfs(v, u);
        }
    }

    void get_diameter()
    {
        for (int i = R; i; i = fa[i])
            diameter[++tot] = i, mark[i] = 1;
        reverse(diameter + 1, diameter + 1 + tot);
        static ll tmp[N];
        memcpy(tmp, dis, sizeof(tmp));
        for (int i = 1; i <= tot; i++)
            dis[i] = tmp[diameter[i]];
    }

    void dfs_d(int u, int f)
    {
        for (int i = Head[u]; i; i = E[i].next)
        {
            int v = E[i].to;
            if (v == f || mark[v]) continue;
            dfs_d(v, u);
            maxx[u] = max(maxx[u], maxx[v] + E[i].w); 
        }
    }

    bool cmp_add(int x, int y)
    {
        return mx[x] + dis[x] > mx[y] + dis[y];
    }

    bool cmp_dec(int x, int y)
    {
        return mx[x] - dis[x] > mx[y] - dis[y];
    }

    struct BitTree
    {
        #define lowbit(x) x&(-x)
        ll c[N];

        inline void clear()
        {
            for (int i = 1; i <= n; i++) c[i] = -inf;
        }

        inline void insert(int x, ll val)
        {
            for (; x; x -= lowbit(x)) c[x] = max(c[x], val);
        }

        inline ll query(int x)
        {
            ll ans = -inf;
            for (; x <= n; x += lowbit(x)) ans = max(ans, c[x]);
            return ans;
        }
    }Bit0,Bit1;

    inline bool check(ll mid)
    {
        Bit0.clear(), Bit1.clear();
        ll lim1 = -inf, lim2 = -inf, lim3 = -inf, lim4 = -inf;
        int j = 1;
        for (int i = tot; i; i--)
        {
            int now = dec[i];
            while (j <= tot && mx[now] - dis[now] + mx[add[j]] + dis[add[j]] > mid)
            {
                Bit0.insert(add[j], mx[add[j]] + dis[add[j]]);
                Bit1.insert(add[j], mx[add[j]] - dis[add[j]]);
                j++;
            }
            ll x0 = Bit0.query(now + 1), x1 = Bit1.query(now + 1);
            if (x0 != -inf && x1 != -inf)
            {
                lim1 = max(lim1, mx[now] - dis[now] + x0 + len - mid);
                lim2 = max(lim2, mx[now] + dis[now] + x0 + len - mid);
                lim3 = max(lim3, mx[now] - dis[now] + x1 + len - mid);
                lim4 = max(lim4, mx[now] + dis[now] + x1 + len - mid);
            }
        }
        int l = tot + 1, r = 0;
        for (int i = tot; i; i--)
        {
            ll Max = min(-lim4 + dis[i], -lim3 - dis[i]); 
            ll Min = max(lim1 + dis[i], lim2 - dis[i]);
            while (r < tot && dis[r + 1] <= Max) r++;
            while (l > 1 && dis[l - 1] >= Min) l--;
            while (r >= 1 && dis[r] > Max) r--;
            while (l <= tot && dis[l] < Min) l++;
            if (l <= r && r >= i) return true;
        }
        return false;
    }

    void work()
    {
        while (1)
        {
            n = read(), len = read();
            init();
            if(!n && !len) break;
            for (int i = 1; i < n; i++)
            {
                int u = read(), v = read(), w = read();
                insert(u, v, w), insert(v, u, w);
            }
            L = 0, R = 0;
            dfs(1, 0);
            for (int  i = 1; i <= n; i++)
                if(dis[i] > dis[L]) L = i;
            dis[L] = 0;
            dfs(L, 0);
            for (int  i = 1; i <= n; i++)
                if(dis[i] > dis[R]) R = i;
            get_diameter();
            ll l = 0, r = 0, mid, ans = -1;
            for (int i = 1; i <= tot; i++) 
                dfs_d(diameter[i], 0), l = max(l, mx[i]);
            r = dis[tot] + (l << 1);
            for (int i = 1; i <= tot; i++) 
                dec[i] = add[i] = i,mx[i] = maxx[diameter[i]];
            sort(add + 1, add + 1 + tot, cmp_add);
            sort(dec + 1, dec + 1 + tot, cmp_dec);
            while (l <= r)
            {
                mid = (l + r) >> 1;
                if (check(mid)) ans = mid, r = mid - 1;
                else l = mid + 1;
            }
            printf("%lld\n", ans);
        }
    }
} 

int main()
{
    TYC::work();
    return 0;
}
