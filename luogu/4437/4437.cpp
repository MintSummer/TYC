#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cstring>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N = 500010;
	int n, cnt, Head[N], a[N], vis[N], belong[N], fa[N], size[N];
	ll ans, val[N];
	
	inline ll read()
	{
		ll x = 0; int f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		return f ? -x : x;
	}
	
	struct edge
	{
		int to, next;
	}E[N];
	
	inline void add(int u, int v)
	{
		E[++cnt] = (edge){v, Head[u]};
		Head[u] = cnt;
	}
	
	bool dfs(int u)
	{
		if (vis[u]) return true;
		vis[u] = 1;
		for (int i = Head[u]; i; i = E[i].next)
			if (dfs(E[i].to)) return true;
		return false;
	}
	
	struct node
	{
		int root, size;
		ll w;
		node(int id, int sz, ll val) : root(id), size(sz), w(val) {}
		bool operator < (const node &t) const
		{
			return w * t.size > size * t.w; 
		}
	};
	priority_queue<node> q;
	
	int find(int x)
	{
		return x == belong[x] ? x : belong[x] = find(belong[x]);
	}
	
	void work()
	{
		n = read();
		for (int i = 1; i <= n; i++)
		{
			a[i] = read();
			add(a[i], i);
			fa[i] = a[i];
		}
		for (int i = 0; i <= n; i++)
			if (!vis[i] && dfs(0)) {puts("-1"); return;}
		for (int i = 1; i <= n; i++)
		{
			belong[i] = i;
			size[i] = 1;
			val[i] = read();
			q.push(node(i, 1, val[i]));
		}
		size[0] = 1;
		while (!q.empty())
		{
			node now = q.top();
			q.pop();
			int u = find(now.root);
			if (size[u] != now.size) continue;
			int f = find(fa[u]);
			belong[u] = f;
			ans += val[u] * size[f];
			size[f] += size[u];
			val[f] += val[u];
			if (f) q.push(node(f, size[f], val[f]));
		}
		printf("%lld\n", ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
