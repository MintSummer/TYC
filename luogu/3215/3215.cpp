#include<bits/stdc++.h>
using namespace std;
const int N=100010,inf=0x3f3f3f3f;

namespace TYC
{
	int n, m, cnt, rt, a[N], val[N], sum[N], size[N], fa[N], son[N][2], pre[N][2], suf[N][2], rep[N], rev[N], fli[N];
	char ch[N],q[10],ins[N];

	inline void update(int root)
	{
		int l = son[root][0], r = son[root][1];
		sum[root] = sum[l] + sum[r] + val[root];
		size[root] = size[l] + size[r] + 1;
		pre[root][0] = min(pre[l][0], sum[l] + val[root] + pre[r][0]);
		pre[root][1] = max(pre[l][1], sum[l] + val[root] + pre[r][1]);
		suf[root][0] = min(suf[r][0], suf[l][0] + val[root] + sum[r]);
		suf[root][1] = max(suf[r][1], suf[l][1] + val[root] + sum[r]);
	}
	
	inline void Replace(int root, int v)
	{
		if (!root) return;
		val[root] = v;
		rep[root] = v;
		rev[root] = 0;
		sum[root] = size[root] * v;
		int d = v == 1 ? 1 : 0;
		pre[root][d^1] = suf[root][d^1] = 0;
		pre[root][d] = suf[root][d] = sum[root];  
	}

	inline void Flip(int root)
	{
		if (!root) return;
		fli[root] ^= 1;
		swap(son[root][0], son[root][1]);
		swap(pre[root][0], suf[root][0]);
		swap(pre[root][1], suf[root][1]);
	}
	
	inline void Reverse(int root)
	{
		if (!root) return;
		rev[root] ^= 1;
		val[root] = -val[root];
		sum[root] = -sum[root];
		swap(pre[root][0], pre[root][1]);
		swap(suf[root][0], suf[root][1]);
		pre[root][0] = -pre[root][0], pre[root][1] = -pre[root][1];
		suf[root][0] = -suf[root][0], suf[root][1] = -suf[root][1];
	}

	inline void pushdown(int root)
	{
		if (fli[root])
		{
			Flip(son[root][0]), Flip(son[root][1]);
			fli[root] = 0;
		}
		if (rep[root])
		{
			Replace(son[root][0], rep[root]);
			Replace(son[root][1], rep[root]);
			rep[root] = 0;
		}
		if (rev[root])
		{
			Reverse(son[root][0]);
			Reverse(son[root][1]);
			rev[root]=0;
		}
	}

	inline int  getdir(int root)
	{
		return son[fa[root]][1] == root;
	}

	inline void rotate(int root)
	{
		int f = fa[root], ff = fa[f];
		int d = getdir(root);
		pushdown(f);
		pushdown(root);

		if (ff) son[ff][getdir(f)] = root;
		else rt = root;
	   	fa[root] = ff;

		son[f][d] = son[root][d^1];
		if(son[root][d^1]) fa[son[root][d^1]] = f;

		son[root][d^1] = f;
		fa[f] = root;

		update(f);
		update(root);	
	}

	inline void splay(int root, int goal)
	{
		while (fa[root] != goal)
		{
			int f = fa[root], ff = fa[f];
			if (ff != goal)
				rotate(getdir(f) ^ getdir(root) ? root : f);
			rotate(root);
		}
	}

	int build(int l, int r,int f)
	{
		if (l > r) return 0;
		int mid = (l + r) >> 1, now = ++cnt;
		fa[now] = f;
		val[now] = a[mid];
		son[now][0] = build(l, mid-1, now);
		son[now][1] = build(mid+1, r, now);
		update(now);
		return now;
	}

	int get_kth(int k)
	{
		int root = rt;
		while (1)
		{
			pushdown(root);
			if (size[son[root][0]] >= k)
				root = son[root][0];
			else 
			{
				k -= size[son[root][0]] + 1;
				if (!k) return root;
				else root = son[root][1]; 
			}
		}
	}

	inline int get_interval(int l, int r)
	{
		int x  = get_kth(l), y = get_kth(r+2);
		//因为在前后都放了一个防止越界,故l即为实际的(l-1),r+2即为实际的(r+1)
		//这样son[y][0]就刚好为[l, r]区间了
		splay(x, 0), splay(y, x);
		return y;
	}

	void work()
	{
		scanf("%d%d%s", &n, &m, ch + 2);
		for (int i = 2; i <= n + 1; i++)
			a[i] = (ch[i] == '(' ? 1 : -1 );
		rt = build(1, n + 2, 0);
		int l, r;
		while (m--)
		{
			scanf("%s%d%d", q, &l, &r);
			int x = get_interval(l, r);
			if (q[0] == 'R') scanf("%s", ins);
			switch (q[0])
			{
				case 'R': Replace(son[x][0],(ins[0] == '(' ? 1 : -1)); break;
				case 'S': Flip(son[x][0]); break;
				case 'I': Reverse(son[x][0]); break;
				case 'Q': printf("%d\n", (suf[son[x][0]][1] + 1) / 2 - (pre[son[x][0]][0] - 1) / 2); break;
			}
			if (q[0] != 'Q') update(x), update(fa[x]); 
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
