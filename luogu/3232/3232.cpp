#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
	const int N = 510, M = N * N;
	const double eps = 1e-6;
	int n, m, cnt, Head[N], from[M], to[M], deg[N];
	double f[N][N], p[N];
	
	inline int read()
	{
		int x = 0, fl = 0; char ch = getchar();
		while(!isdigit(ch)) fl |= (ch == '-'), ch = getchar();
		while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		return fl ? -x : x;
	}
	
	struct edge
	{
		int to, next;
	}E[M];
	
	inline void add(int u, int v)
	{
		E[++cnt] = (edge){v, Head[u]};
		Head[u] = cnt;
	}
	
	void Gauss()
	{
		for (int i = 1; i < n; i++)
		{
			int pos = i;
			for (int j = i + 1; j < n; j++)
				if (fabs(f[j][i]) - fabs(f[pos][i]) > eps) pos = j;
			if (pos != i)
				for (int j = 1; j <= n; j++) swap(f[i][j], f[pos][j]);
			for (int j = 1; j <= n; j++) if (i != j)
			{
				double tmp = f[j][i] / f[i][i];
				for (int k = i + 1; k <= n; k ++)
					f[j][k] -= f[i][k] * tmp;
			}
		}
		for (int i = 1; i <= n; i++) f[i][n] /= f[i][i];
	}
	
	bool cmp (const double x, const double y)
	{
		return x > y;
	}
	
	void work()
	{
		n = read(), m =read();
		for (int i = 1; i <= m; i++)
		{
			int u = read(), v = read();
			add(u, v), add(v, u);
			from[i] = u, to[i] = v;
			deg[u]++, deg[v]++;
		}
		f[1][n] = 1;
		for (int u = 1; u < n; u++)
		{
			f[u][u] = 1;
			for (int i = Head[u]; i; i = E[i].next)
			{
				int v = E[i].to;
				if (v == n) continue;
				f[u][v] = -1.0 / deg[v];
			}
		}
		Gauss();
		for (int i = 1; i <= m; i++)
		{
			if (from[i] != n)
				p[i] += f[from[i]][n] * 1.0 / deg[from[i]];
			if (to[i] != n)
				p[i] += f[to[i]][n] * 1.0 / deg[to[i]];
		}
		sort(p + 1, p + 1 + m, cmp);
		double ans = 0;
		for (int i = 1; i <= m; i++) ans += p[i] * i;
		printf("%.3f", ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
