#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

namespace TYC
{
    const int N = 1000010;
    int n, cnt, Head[N], size[N];
    long long dis[N], sum[N];

    inline int read()
    {
        int x = 0, f = 0; char ch = getchar();
        while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
        return f ? -x : x;
    }

    struct edge
    {
        int to, next;
    }E[N << 1];

    inline void add(int u, int v)
    {
        E[++cnt] = (edge){v, Head[u]};
        Head[u] = cnt;
    }

    void dfs(int u, int f)
    {
        size[u] = 1;
        for (int i = Head[u]; i; i = E[i].next)
        {
            int v = E[i].to;
            if (v == f) continue;
            dfs(v, u);
            size[u] += size[v];
            dis[u] += dis[v] + size[v];
        }
    }

    void get_ans(int u, int f)
    {
        for (int i = Head[u]; i; i = E[i].next)
        {
            int v = E[i].to;
            if (v == f) continue;
            sum[v] = sum[u] - size[v] + (n - size[v]);
            get_ans(v, u);
        }
    }

    void work()
    {
        n = read();
        for (int i = 1; i < n; i++)
        {
            int u = read(), v = read();
            add(u, v), add(v, u);
        }
        dfs(1, 0);
        sum[1] = dis[1];
        get_ans(1, 0);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            if(sum[i] > sum[ans]) ans = i;
        printf("%d\n", ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}