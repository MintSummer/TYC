#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

namespace TYC
{
	const double eps=1e-4;
	const int N = 1010;
	int n, root, cnt, Head[N], val[N], sz[N], fa[N], belong[N];
	
	inline int read()
	{
		int x = 0, f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		return f ? -x : x;
	}
	
	int find(int x)
	{
		return x == belong[x] ? x : belong[x] = find(belong[x]);
	}
	
	inline int FindMin()
	{
		int now = 0;
		for (int i = 1; i <= n; i++)
			if (!now || (double)val[i] / sz[i] - (double)val[now] / sz[now] >= eps) now = i;
		return now; 
	}
	
	void work()
	{
		while (1)
		{
			n = read(), root = read();
			if (!n) return;
			memset(fa, 0, sizeof(int[n + 1]));
			for (int i = 1;i <= n; i++)
			{
				val[i] = read();
				sz[i] = 1;
				belong[i] = i;
			}
			for (int i = 1; i < n; i++)
			{
				int u = read(), v = read();
				fa[v] = u;
			}
			int ans = 0;
			sz[0] = 1;
			while (1)
			{
				int u = FindMin();
				if (!val[u]) break;
				int f = find(fa[u]);
				belong[u] = f;
				ans += sz[f] * val[u];
				val[f] += val[u], sz[f] += sz[u];
				val[u] = 0;
			}
			printf("%d\n", ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
