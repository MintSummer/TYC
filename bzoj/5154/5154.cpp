#include <bits/stdc++.h>
using namespace std;

namespace TYC
{
const int N = 1010, M = 300010, inf = 0x3f3f3f3f;
int n, s, t, cnt = 1, ans, Head[N], dis[N], pre[N], check[M], cur[N], cannot[M], mark[N][N];
bool vis[N];

inline int read()
{
	int x = 0, f = 0;
	char ch = getchar();
	while (!isdigit(ch))
		f |= (ch == '-'), ch = getchar();
	while (isdigit(ch))
		x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}

struct edge
{
	int to, w, nx, cost;
} E[M], tmp[M];

inline void add(int u, int v, int w, int c)
{
	E[++cnt] = edge{v, w, Head[u], c};
	Head[u] = cnt;
	E[++cnt] = edge{u, 0, Head[v], -c};
	Head[v] = cnt;
}
int spfa()
{
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= t; i++)
		dis[i] = -inf;
	deque<int> q;
	q.push_back(s);
	vis[s] = 1;
	dis[s] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop_front();
		for (int i = Head[u]; i; i = E[i].nx)
		{
			if (cannot[i])
				continue;
			int v = E[i].to;
			if (E[i].w && dis[u] + E[i].cost > dis[v])
			{
				dis[v] = dis[u] + E[i].cost;
				if (!vis[v])
				{
					vis[v] = 1;
					if (!q.empty() && dis[v] < dis[q.front()])
						q.push_front(v);
					else
						q.push_back(v);
				}
			}
		}
		vis[u] = 0;
	}
	return dis[t] != -inf;
}

int dfs(int u, int flow)
{
	if (u == t)
	{
		vis[u] = 1;
		return flow;
	}
	int used = 0;
	vis[u] = 1;
	for (int &i = cur[u]; i; i = E[i].nx)
	{
		if (cannot[i]) continue;
		int v = E[i].to;
		if ((!vis[v] || v == t) && E[i].w && dis[u] + E[i].cost == dis[v])
		{
			int di = dfs(v, min(E[i].w, flow - used));
			if (di)
				E[i].w -= di, E[i ^ 1].w += di, ans += E[i].cost * di, used += di;
			if (used == flow)
				break;
		}
	}
	return used;
}
int zkw()
{
	ans = 0;
	int res = 0;
	while (spfa())
	{
		vis[t] = 1;
		for (int i = 1; i <= t; i++)
			cur[i] = Head[i];
		while (vis[t])
		{
			memset(vis, 0, sizeof(vis));
			res += dfs(s, inf);
		}
	}
	return ans;
}

void work()
{
	n = read();
	s = n + n + 1, t = s + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			add(i, j + n, 1, read());
	for (int i = 1; i <= n; i++)
		add(s, i, 1, 0), add(i + n, t, 1, 0);
	memcpy(tmp, E, sizeof(tmp));
	int tot = 0, max_sum = zkw();
	printf("%d\n", max_sum);
	for (int i = 2; i <= cnt; i += 2)
		if (!E[i].w)
			check[i] = 1;
	for (int i = 2; i <= cnt; i += 2)
		if (check[i] && E[i].to != t && E[i ^ 1].to != s)
		{
			cannot[i] = cannot[i ^ 1] = 1;
			memcpy(E, tmp, sizeof(tmp));
			int s = zkw();
			if (s < max_sum)
				mark[E[i ^ 1].to][E[i].to] = 1;
			cannot[i] = cannot[i ^ 1] = 0;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (mark[i][j + n])
				printf("%d %d\n", i, j);
}
} // namespace TYC

int main()
{
	TYC::work();
	return 0;
}