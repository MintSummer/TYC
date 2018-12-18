#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
	const int N = 1000010;
	int n, m, cnt, root, a[N], ans[N];
	
	namespace IO
	{
		inline int read()
		{
			int x = 0, f = 0; char ch = getchar();
			while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
			while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
			return f ? -x : x;
		}
		
		inline void write(int x)
		{
			if (x < 0) putchar('-'), x = -x;
			if (!x) putchar('0');
			else
			{
				int len = 0;
				static int bask[20];
				while (x) bask[++len] = x % 10, x /= 10;
				for (; len; len--) putchar('0' + bask[len]);
			}
			putchar('\n');
		}
	}
	
	using IO::read;
	using IO::write;
	
	struct ques
	{
		int id, val;
		bool operator < (const ques &t) const
		{
			return val < t.val;
		}
	}q[N];
	
	namespace ZPT
	{
		const int M = N << 1;
		int val[M], fa[M], dis[M], son[M][2], size[M];
		#define ls son[x][0]
		#define rs son[x][1]
		
		inline void update(int x)
		{
			size[x] = size[ls] + size[rs] + 1;
		}
		
		int merge(int x, int y)
		{
			if (!x || !y) return x + y;
			if(val[x] < val[y]) swap(x, y);
			rs = merge(rs, y);
			fa[rs] = x;
			if (dis[ls] < dis[rs]) swap(ls, rs);
			dis[x] = dis[rs] + 1;
			update(x);
			return x;
		}
		
		int find(int x)
		{
			while (fa[x]) x = fa[x];
			return x;
		}
		
		inline void del(int x)
		{
			if (!x) return;
			fa[ls] = fa[rs] = 0;
			root = merge(ls, rs);
			son[x][0] = son[x][1] = 0;
			size[x] = 1;
		}
	}
	
	using ZPT::val;
	using ZPT::merge;
	using ZPT::find;
	using ZPT::size;
	
	inline void solve(int x)
	{
		if (x < 0) 
		{
			val[++cnt] = x;
			size[cnt] = 1;
			root = merge(root = find(root), cnt);
		}
		else while (x)
		{
			int tmp = find(root);
			ZPT::del(tmp);
			if (!tmp && !root) return;
			if (x + val[tmp] > 0) x += val[tmp];
			else 
			{
				val[tmp] += x;
				root = merge(root, tmp);
				break;
			}
		}
		root = find(root);
	}
	
	void work()
	{
		n = read(), m = read();
		for (int i = 1; i <= n; i++) a[i] = read();
		for (int i = 1; i <= m; i++) 
			q[i] = (ques){i, read()};
		sort(q + 1, q + 1 + m);
		for (int i = n; i; i--) solve(a[i]);
		for (int i = 1; i <= m; i++)
		{
			solve(q[i].val);
			ans[q[i].id] = size[root];
		}
		for (int i = 1; i <= m; i++) write(ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
