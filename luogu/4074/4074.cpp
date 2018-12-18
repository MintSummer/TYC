#include <bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N = 1e5 + 10;
	int n, m, ques, cnt, V[N], W[N], Head[N], candy[N];
	
	namespace IO
	{
		inline int read()
		{
			int x = 0, f = 0; char ch = getchar();
			while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
			while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
			return f ? -x : x;
		}
		
		inline void write(ll x)
		{
			if (!x) putchar('0');
			else 
			{
				int len = 0;
				static int bask[50];
				while (x) bask[++len] = x % 10, x /= 10;
				for (; len; len--) putchar('0' + bask[len]);
			}
			putchar('\n');
		}
	}
	
	using IO::read;
	using IO::write;
	
	struct edge
	{
		int to, next;
	}E[N << 1];
	
	inline void add(int u, int v)
	{
		E[++cnt] = (edge){v, Head[u]};
		Head[u] = cnt;
		E[++cnt] = (edge){u, Head[v]};
		Head[v] = cnt;
	}
	
	namespace BruteForce // 30pts 
	{
		int fa[N], list[N], dep[N], num[N];
		
		void dfs(int u, int f)
		{
			fa[u] = f, dep[u] = dep[f] + 1;
			for (int i = Head[u]; i; i = E[i].next)
			{
				int v = E[i].to;
				if (v == f) continue;
				dfs(v, u);
			}
		}
		
		inline int LCA(int u, int v)
		{
			if (dep[u] < dep[v]) swap(u, v);
			while (dep[u] > dep[v]) u = fa[u];
			if (u == v) return u;
			while (u != v) u = fa[u], v = fa[v];
			return u;
		}
		
		void solve(int u, int v)
		{
			int lca = LCA(u, v), len = dep[u] + dep[v] - dep[lca] * 2 + 1;
			int l = 0, r = len;
			while (u != lca) list[++l] = u, u = fa[u];
			while (v != lca) list[r--] = v, v = fa[v];
			list[++l] = lca;
			ll ans = 0;
			memset(num, 0, sizeof(num));
			for (int i = 1; i <= len; i++)
			{
				int x = list[i], c = candy[x];
				num[c]++;
				ans += (ll)W[num[c]] * V[c];
			}
			write(ans);
		}
		
		void work()
		{
			dfs(1, 0);
			while(ques--)
			{
				int opt = read();
				if (opt) solve(read(), read());
				else candy[read()] = read();
			}
		}
	}
	
	namespace SubtaskLink // 40pts 
	{
		int totq, totc, block, num, belong[N], end[N], dis[N], fa[N], id[N], list[N], tot[N];
		ll ans, Ans[N];
		
		struct Question
		{
			int l, r, pre, id;
			Question(){}
			Question(int _l, int _r, int _pre, int _id) : l(_l), r(_r), pre(_pre), id(_id) 
			{
				if(l > r) swap(l, r);
			}
			
			bool operator < (const Question &t) const
			{
				if (belong[l] != belong[t.l]) return belong[l] < belong[t.l];
				if (belong[r] != belong[t.r]) return belong[r] < belong[t.r];
				return pre < t.pre;
			}
		}q[N];
		
		struct Modify
		{
			int pos, candy;
			Modify(){}
			Modify(int p, int ca) : pos(p), candy(ca) {}
		}c[N];
		
		void dfs(int u, int f)
		{
			fa[u] = f, dis[u] = dis[f] + 1;
			for (int i = Head[u]; i; i = E[i].next)
				if (E[i].to != f) dfs(E[i].to, u);
		}
		
		void init()
		{
			block = pow(n, 0.66667);
			for (int i = 1; i <= n; i++)
				belong[i] = (i - 1) / block + 1;
			num = belong[n];
			for (int i = 1; i <= num; i++)
				end[i] = end[i - 1] + block;
		}
		
		inline void add(int pos, int tag)
		{
			int ca = candy[list[pos]];
			if (~tag) 
				ans += (ll)W[++tot[ca]] * V[ca];
			else 
				ans -= (ll)W[tot[ca]--] * V[ca];
		}
		
		inline void change(int x, int y)
		{
			int p = list[c[x].pos], ca = c[x].candy;
			if (q[y].l <= c[x].pos && c[x].pos <= q[y].r)
			{
				ans -= (ll)W[tot[candy[p]]--] * V[candy[p]];
				ans += (ll)W[++tot[ca]] * V[ca];
			}
			swap(candy[p], c[x].candy);
		}
		
		void work(int start, int ed)
		{
			for (int i = n; i; i--, ed = fa[ed])
				list[i] = ed, id[ed] = i; 
			init();
			for (int i = 1; i <= ques; i++)
			{
				int opt = read();
				if (opt)
				{
					totq++;
					int u = read(), v = read();
					q[totq] = Question(id[u], id[v], totc, totq); 
				}
				else 
				{
					totc++;
					int x = read(), ca = read();
					c[totc] = Modify(id[x], ca); 
				}
			}
			sort(q + 1, q + 1 + totq);
			
			int l = 1, r = 0, last = 0;
			for (int i = 1; i <= totq; i++)
			{
				while (l < q[i].l) add(l++, -1);
				while (l > q[i].l) add(--l, 1);
				while (r < q[i].r) add(++r, 1);
				while (r > q[i].r) add(r--, -1);
				while (last < q[i].pre) change(++last, i);
				while (last > q[i].pre) change(last--, i);
				Ans[q[i].id] = ans;
			}
			for (int i = 1; i <= totq; i++)	write(Ans[i]);
		}
		
		bool CheckLink()
		{
			int start = 0, ed = 0;
			SubtaskLink::dfs(1, 0);
			for (int i = 1; i <= n; i++)
				if (dis[i] > dis[start]) start = i;
			SubtaskLink::dfs(start, 0);
			for (int i = 1; i <= n; i++)
				if (dis[i] > dis[ed]) ed = i;
			if (dis[ed] == n) 
			{
				SubtaskLink::work(start, ed);
				return true;
			}
			return false;
		}
	}
	
	namespace Accept
	{		
		typedef pair<int, int> pa;
		const int M = N << 1;
		int dfn, all, totq, totc, block, num;
		int belong[M], end[M], list[M], dep[N], tot[M], fa[N][20], vis[N];
		ll ans, Ans[M];
		pa pos[M];
		
		struct Question
		{
			int u, v, pre, id;
			Question(){}
			Question(int _u, int _v, int _pre, int _id) : 
				u(_u), v(_v), pre(_pre), id(_id) 
			{
				if(pos[u].first>pos[v].first) swap(u,v);
			}
			
			bool operator < (const Question &t) const
			{
				if (belong[pos[u].first] != belong[pos[t.u].first]) 
					return belong[pos[u].first] < belong[pos[t.u].first];
				if (belong[pos[v].first] != belong[pos[t.v].first]) 
					return belong[pos[v].first] < belong[pos[t.v].first];
				return pre < t.pre;
			}
		}q[M];
		
		struct Modify
		{
			int id, candy;
		}c[M];
		
		void dfs(int u, int f)
		{
			dep[u] = dep[f] + 1;
			list[++all] = u;
			pos[u].first = all;
			fa[u][0] = f;
			for (int i = 1; fa[u][i - 1] && i <= 18; i++)
				fa[u][i] = fa[fa[u][i - 1]][i - 1];
			for (int i= Head[u]; i; i = E[i].next)
			{
				int v = E[i].to;
				if (v == f) continue;
				dfs(v, u);
			}
			list[++all] = u;
			pos[u].second = all;
		}
		
		inline int LCA(int u, int v)
		{
			if (dep[u] < dep[v]) swap(u, v);
			for (int d = dep[u] - dep[v], t = 0; d; d >>= 1, t++)
				if (d & 1) u = fa[u][t];
			if (u == v) return u;
			for (int i = 18; i >= 0; i--)
				if (fa[u][i] != fa[v][i])
					u = fa[u][i], v = fa[v][i];
			return fa[u][0];
		}
		
		void init()
		{
			block = pow(n, 0.66667);
			for (int i = 1; i <= n; i++)
				belong[i] = (i - 1) / block + 1;
			num = belong[n];
			for (int i = 1; i <= num; i++)
				end[i] = end[i - 1] + block;
		}
		
		inline void add(int x)
		{
			vis[x] ^= 1;
			int tag = vis[x], ca = candy[x];
			if (tag) 
				ans += (ll)W[++tot[ca]] * V[ca];
			else 
				ans -= (ll)W[tot[ca]--] * V[ca];
		}
		
		inline void change(int x, int y)
		{
			int p = c[x].id, ca = c[x].candy;
			if (vis[p])
			{
				ans -= (ll)W[tot[candy[p]]--] * V[candy[p]];
				ans += (ll)W[++tot[ca]] * V[ca];
			}
			swap(candy[p], c[x].candy);
		}
		
		void work()
		{
			n <<= 1;
			dfs(1, 0);
			init();
			for (int i = 1; i <= ques; i++)
			{
				int opt = read();
				if (opt)
					totq++, q[totq] = Question(read(), read(), totc, totq); 
				else 
					c[++totc] = (Modify){read(), read()}; 
			}
			sort(q + 1, q + 1 + totq);
			int l = 1, r = 0, last = 0;
			for (int i = 1; i <= totq; i++)
			{
				int u = q[i].u, v = q[i].v, lca = LCA(u, v);
				int ql = pos[u].first, qr = pos[v].first;
				while (l < ql) add(list[l++]);
				while (l > ql) add(list[--l]);
				while (r < qr) add(list[++r]);
				while (r > qr) add(list[r--]);
				while (last < q[i].pre) change(++last, i);
				while (last > q[i].pre) change(last--, i);
				if (u != lca)
				{
					add(u);
					if (v != lca) add(lca);
				}
				Ans[q[i].id] = ans;
				if (u != lca)
				{
					add(u);
					if (v != lca) add(lca);
				}
			}
			for (int i = 1; i <= totq; i++)	write(Ans[i]);
		}
	}
	
	void work()
	{
		n = read(), m = read(), ques = read();
		for (int i = 1; i <= m; i++) V[i] = read();
		for (int i = 1; i <= n; i++) W[i] = read();
		for (int i = 1; i < n; i++) 
		{
			int u = read(), v = read();
			add(u, v);
		}
		for (int i = 1; i <= n; i++) candy[i] = read();
	  	if (n <= 10000) BruteForce::work();
		else if (!SubtaskLink::CheckLink()) Accept::work();
	}
}

int main()
{
	TYC::work();
	return 0;
}
