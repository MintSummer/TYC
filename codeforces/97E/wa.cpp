#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>
using namespace std;

namespace zyt
{
	template<typename T>
	inline void read(T &x)
	{
		char c;
		bool f = false;
		x = 0;
		do
			c = getchar();
		while (c != '-' && !isdigit(c));
		if (c == '-')
			f = true, c = getchar();
		do
			x = x * 10 + c - '0', c = getchar();
		while (isdigit(c));
		if (f)
			x = -x;
	}
	template<typename T>
	inline void write(T x)
	{
		static char buf[20];
		char *pos = buf;
		if (x < 0)
			putchar('-'), x = -x;
		do
			*pos++ = x % 10 + '0';
		while (x /= 10);
		while (pos > buf)
			putchar(*--pos);
	}
	inline void write(const char *const s)
	{
		printf("%s", s);
	}
	const int N = 1e5 + 10, M = 1e5 + 10, B = 18;
	int n, m, ecnt, head[N];
	struct edge
	{
		int to, next;
	}e[M << 1];
	bool mark[M << 1];
	int dfn[N], dfncnt, euler[N << 1], dep[N];
	inline void add(const int a, const int b)
	{
		e[ecnt] = (edge){b, head[a]}, head[a] = ecnt++;
	}
	namespace BCC
	{
		int bcc, top, belong[M << 1], stack[M << 1], low[N];
		bool vis[M << 1];
		vector<int> own[N], ownpt[N];
		void Tarjan(const int u, const int from)
		{
			dfn[u] = low[u] = ++dfncnt;
			euler[dfncnt] = u;
			dep[u] = (~from ? dep[e[from ^ 1].to] + 1 : 1);
			for (int i = head[u]; ~i; i = e[i].next)
			{
				int v = e[i].to;
				if (vis[i] || (~from && i == (from ^ 1)))
					continue;
				stack[top++] = i;
				if (dfn[v])
					low[u] = min(low[u], dfn[v]);
				else
				{
					Tarjan(v, i), low[u] = min(low[u], low[v]);
					euler[++dfncnt] = u;
					if (dfn[u] <= low[v])
					{
						int t;
						++bcc;
						ownpt[bcc].push_back(u);
						do
						{
							t = stack[--top];
							belong[t] = belong[t ^ 1] = bcc;
							vis[t] = vis[t ^ 1] = true;
							own[bcc].push_back(t);
							ownpt[bcc].push_back(e[i].to);
						}
						while (t != i);
					}
				}
			}
		}
		void solve()
		{
			for (int i = 1; i <= n; i++)
				if (!dfn[i])
					Tarjan(i, -1);
		}
	}
	namespace ST
	{
		int lg2[N << 1], st[N << 1][B];
		inline int _min(const int a, const int b)
		{
			return dfn[a] < dfn[b] ? a : b;
		}
		void build()
		{
			int tmp = 0;
			for (int i = 1; i <= dfncnt; i++)
			{
				lg2[i] = tmp;
				if (i == (1 << (tmp + 1)))
					++tmp;
			}
			for (int i = dfncnt; i > 0; i--)
			{
				st[i][0] = euler[i];
				for (int j = 1; j < B; j++)
					if (i + (1 << j) - 1 <= dfncnt)
						st[i][j] = _min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
					else
						break;
			}
		}
		inline int query(const int a, const int b)
		{
			int len = b - a + 1;
			return _min(st[a][lg2[len]], st[b - (1 << lg2[len]) + 1][lg2[len]]);
		}
	}
	inline int lca(const int a, const int b)
	{
		return ST::query(min(dfn[a], dfn[b]), max(dfn[a], dfn[b]));
	}
	int p[N];
	int f(const int x)
	{
		return x == p[x] ? x : p[x] = f(p[x]);
	}
	bool vis[N], col[N];
	int w[N];
	bool dfs(const int u, const int from)
	{
		using BCC::belong;
		if (vis[u])
		{
			if (col[u] == col[e[from ^ 1].to])
				return true;
			else
				return false;
		}
		vis[u] = true, col[u] = col[e[from ^ 1].to] ^ 1;
		for (int i = head[u]; ~i; i = e[i].next)
		{
			int v = e[i].to;
			if (belong[i] != belong[from] || i == (from ^ 1))
				continue;
			if (dfs(v, i))
				return true;
		}
		return false;
	}
	void dfs2(const int u, const int from)
	{
		vis[u] = true;
		for (int i = head[u]; ~i; i = e[i].next)
		{
			int v = e[i].to;
			if (vis[v] || ~from && i == (from ^ 1))
				continue;
			w[v] = w[u] + mark[i];
			dfs2(v, i);
		}
	}
	int work()
	{
		using BCC::solve;
		using BCC::bcc;
		using BCC::own;
		using BCC::ownpt;
		read(n), read(m);
		memset(head, -1, sizeof(int[n + 1]));
		for (int i = 1; i <= n; i++)
			p[i] = i;
		for (int i = 0; i < m; i++)
		{
			int a, b;
			read(a), read(b);
			add(a, b), add(b, a);
			p[f(a)] = f(b);
		}
		solve();
		ST::build();
		for (int i = 1; i <= bcc; i++)
		{
			for (int j = 0; j < ownpt[i].size(); j++)
				vis[j] = false;
			if (dfs(e[own[i][0]].to, own[i][0]))
				for (int j = 0; j < own[i].size(); j++)
					mark[own[i][j]] = mark[own[i][j] ^ 1] = true;
		}
		memset(vis, 0, sizeof(bool[n + 1]));
		for (int i = 1; i <= n; i++)
			if (!vis[i])
				dfs2(i, -1);
		int q;
		read(q);
		while (q--)
		{
			int u, v;
			read(u), read(v);
			if (f(u) != f(v))
			{
				write("No\n");
				continue;
			}
			int l = lca(u, v);
			if (((dep[u] + dep[v] - (dep[l] << 1)) & 1) || 
					w[u] + w[v] - (w[l] << 1))
				write("Yes\n");
			else
				write("No\n");
		}
		return 0;
	}
}
int main()
{
	return zyt::work();
}
