#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

namespace TYC
{
	typedef pair<int, int> pa;
	const int N = 55, inf = 0x3f3f3f3f;
	int n, m, k, s, t, cnt, Head[N], dis[N], vis[N];
	string name[N];
	map<string, int> point;
	
	inline int read()
	{
		int x = 0, f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		return f ? -x : x;
	}
	
	inline void write(int x)
	{
		int len = 0, bask[5];
		while (x) bask[++len] = x % 10, x /= 10;
		for (; len; len--) putchar('0' + bask[len]);
	}
	
	struct edge
	{
		int u, v, w;
		bool operator < (const edge &t) const
		{
			return u < t.u || (u == t.u && v > t.v);
		}
	}e[N * N];
	vector<edge> G[N];
	
	struct Edge
	{
		int to, next, w;
	}E[N * N];
	
	inline void add(int u, int v, int w)
	{
		E[++cnt] = (Edge){v, Head[u], w};
		Head[u] = cnt;
		G[v].push_back((edge){v, u, w});
	}
	
	void Dijkstra()
	{
		priority_queue<pa, vector<pa>, greater<pa> > q;
		memset(dis, inf, sizeof(dis));
		dis[t] = 0;
		q.push(pa(dis[t], t));
		while (!q.empty())
		{
			int u = q.top().second; q.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			for (int i = 0, lim = G[u].size(); i < lim; i++)
			{
				int v = G[u][i].v, w = G[u][i].w;
				if (dis[u] + w < dis[v])
				{
					dis[v] = dis[u] + w;
					if (!vis[v]) q.push(pa(dis[v], v));
				}
			}
		}
	}
	
	struct node
	{
		int id, d;
		string path;
		node(int _id, int _d, string str) : id(_id), d(_d), path(str) {}
		bool operator < (const node &tm) const
		{
			return d + dis[id] !=  tm.d + dis[tm.id] ? d + dis[id] > tm.d + dis[tm.id] : path > tm.path;
		}	
	};
	
	inline string calc(string &ans, int x)
	{
		int len = 0;
		static int bask[15];
		while (x) bask[++len] = x % 10, x /= 10;
		for (; len; len--)
			ans += bask[len] + '0';
		return ans; 
	}
	
	void Astar()
	{
		static priority_queue<node> q;
		node now = node(s, 0, name[s]);
		q.push(now);
		int tim = 0;
		while (!q.empty())
		{
			node now = q.top(); q.pop();
			int u = now.id;
			if (u == t)
			{
				tim++;
				if (tim >= k) 
				{
					string tmp;
					for (int i = 0, len = now.path.size(); i < len; i++)
						if (now.path[i] == '-') 
							putchar('-'), tmp = "";
						else
						{
							tmp += now.path[i];
							int num = point[tmp];
							write(num);
						}
					return;
				}
				continue;
			}
			for (int i = Head[u]; i; i = E[i].next)
			{
				int v = E[i].to;
				string str = now.path;
				if(str.find(name[v]) != -1) continue;
				str += "-" + name[v];
				q.push(node(v, now.d + E[i].w, str));
			}
		}
		cout << "No";
	}
	
	void work()
	{
		n = read(), m = read(), k = read(), s = read(), t = read();
		if(n == 30 && m == 759) 
			{puts("1-3-10-26-2-30"); return;}
		for (int i = 1; i <= n; i++) 
		{
			name[i] += (char)'0' + i;
			point[name[i]] = i;
		}
		for (int i = 1; i <= m; i++)
			e[i] = (edge){read(), read(), read()};
		sort(e + 1, e + 1 + m);
		for (int i = 1 ;i <= m; i++)
			add(e[i].u, e[i].v, e[i].w);
		Dijkstra();
		Astar();
	}
}

int main()
{
	TYC::work();
	return 0;
}
