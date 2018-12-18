#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5,inf = 2147483647;

namespace Treap
{
    int tot = 0;
    struct node
    {
		int val, size, cnt, fix, son[2];
    }tree[MAXN*20];

    int newnode(int x)
    {
		tree[++tot] = (node){x, 1, 1, rand(), 0, 0};
		return tot;
    }

    void update(int root)
    {
		tree[root].size = tree[root].cnt + tree[tree[root].son[0]].size + tree[tree[root].son[1]].size;
    }

    void rotate(int &root, int d)
    {	
		int s = tree[root].son[d];
		tree[root].son[d] = tree[s].son[d ^ 1];
		tree[s].son[d ^ 1] = root;
		update(root);
		update(s);
		root = s;
    }

    void insert(int &root, int x)
    {
		if (!root) 
			root = newnode(x);
		else if (tree[root].val == x) 
			tree[root].cnt++;
		else 
		{
			int d = (tree[root].val > x ? 0 : 1);
			insert(tree[root].son[d], x);
			if (tree[tree[root].son[d]].fix > tree[root].fix)
				rotate(root,d);
		}
		update(root);
    }

    void del(int &root, int x)
    {
		if (tree[root].val >  x) 
			del(tree[root].son[0], x);
		else if (tree[root].val < x)
			del(tree[root].son[1], x);
		else if (tree[root].cnt > 1) 
			tree[root].cnt--;
		else
		{
			if (!tree[root].son[0] && !tree[root].son[1]) 
			root = 0;
			else if (!tree[root].son[0])
			{
				rotate(root, 1);
				del(tree[root].son[0], x);
			}
			else if(!tree[root].son[1])
			{
				rotate(root, 0);
				del(tree[root].son[1], x);
			}
			else
			{
				if(tree[tree[root].son[0]].fix > tree[tree[root].son[1]].fix)
				{
					rotate(root, 0);
					del(tree[root].son[1], x);
				}
				else 
				{
					rotate(root, 1);
					del(tree[root].son[0], x);
				}
			}
		}
		if(root) update(root);
    }

    int rank(int root, int k)
    {
		if (!root) return 0;
		if (tree[root].val > k)
			return rank(tree[root].son[0], k);
		else if (tree[root].val == k) 
			return tree[tree[root].son[0]].size;
		else
			return tree[tree[root].son[0]].size + tree[root].cnt + rank(tree[root].son[1], k);
    }

    int pre(int root, int k)
    {
		if (!root) return -inf;
		if (tree[root].val >= k)
			return pre(tree[root].son[0], k);
		else 
			return max(tree[root].val, pre(tree[root].son[1], k));
    }

    int suc(int root, int k)
    {
		if (!root) return inf;
		if (tree[root].val <= k)
			return suc(tree[root].son[1], k);
		else
			return min(tree[root].val, suc(tree[root].son[0], k));
    }
}

namespace TYC
{
    int n, m, a[MAXN];

    inline int read()
    {
		int x = 0, f = 0;
		char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		return f ? -x : x;
    }

    struct segment_node
    {
		int l, r, root;
    }tree[MAXN*8];

    void build(int root, int l, int r)
    {
		tree[root].l = l, tree[root].r = r;
		for (int i = l; i <= r; i++)
			Treap::insert(tree[root].root, a[i]);
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(root * 2, l, mid);
		build(root * 2 + 1, mid + 1, r);
    }

    int rank(int root, int l, int r, int k)
    {
		if (tree[root].l > r || tree[root].r < l) return 0;
		if (l <= tree[root].l && tree[root].r <= r) 
			return Treap::rank(tree[root].root, k);
		else
			return rank(root * 2, l, r, k) + rank(root * 2 + 1, l, r, k);
    }

    int num(int l, int r, int k)
    {
		int lt = 0, rt = 1e8;
		while (lt < rt)
		{
			int mid = (lt + rt + 1) / 2;
			if (rank(1, l, r, mid) < k) lt = mid;
			else rt = mid - 1;
		}
		return rt;
    }

    void change(int root, int x, int val)
    {
		Treap::del(tree[root].root, a[x]);
		Treap::insert(tree[root].root, val);
		int l = tree[root].l, r = tree[root].r;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (x <= mid) change(root * 2, x, val);
		else change(root * 2 + 1, x, val);
    }

    int pre(int root, int l, int r, int k)
    {
		if (tree[root].l > r || tree[root].r < l) 
			return -inf;
		if (tree[root].l >= l && tree[root].r <= r)
			return Treap::pre(tree[root].root, k);
		else 
			return max(pre(root * 2, l, r, k), pre(root * 2 + 1, l, r, k));
    }

    int suc(int root, int l, int r, int k)
    {
		if (tree[root].l > r || tree[root].r < l)
			return inf;
		if (tree[root].l >= l && tree[root].r <= r)
			return Treap::suc(tree[root].root, k);
		else
		    return min(suc(root * 2, l, r, k), suc(root * 2 + 1, l, r,k));
    }

    void work()
    {
		n = read(), m = read();
		for (int i = 1; i <= n; i++) a[i] = read();
		build(1, 1, n);
		int opt, l, r, k, pos;
		while (m--)
		{
			opt = read();
			if (opt == 3) 
			{
				pos = read(), k = read();
				change(1, pos, k);
				a[pos] = k;
			}
			else 
			{
				l = read(), r = read(), k = read();
				switch (opt)
				{
					case 1:	
						printf("%d\n", rank(1, l, r, k) + 1);//要算上自己
						break;
					case 2:
						printf("%d\n", num(l, r, k));
						break;
					case 4:
						printf("%d\n", pre(1, l, r, k));
						break;
					case 5:
						printf("%d\n", suc(1, l, r, k));
						break;
				}
			}
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
