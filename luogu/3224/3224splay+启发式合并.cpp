#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int MAXN=100010;
    int n,m,q,rank[MAXN],fa[MAXN];

    struct Splay
    {
		struct node
		{
			int val,id,size;
			node *fa,*son[2];
			node(int val, int id, node *fa): val(val),id(id),fa(fa)
			{
				size=1;
				son[0]=son[1]=NULL;
			}
		}*head;

		void update(node *root)
		{
			root->size = 1;
			if (root->son[0]) 
				root->size += root->son[0]->size;
			if (root->son[1])
				root->size += root->son[1]->size;
		}

		int getdir(node *root) 
		{
			return root == root->fa->son[1];
		}

		void rotate(node *root)
		{
			int d=getdir(root);
			node *f = root->fa, *ff = f->fa;
			root->fa = ff;

			if (ff) ff->son[getdir(f)] = root;
			else head = root;

			f->son[d] = root->son[!d];
			if(root->son[!d]) root->son[!d]->fa = f;

			f->fa = root;
			root->son[!d] = f;

			update(f);
			update(root);
		}

		void splay(node *root)
		{
			while (root && root->fa)
			{
				node *f = root->fa, *ff = f->fa;
				if (ff) 
				    rotate(getdir(root) ^ getdir(f) ? root : f);
				rotate(root);
			}
		}

		void insert(int val, int id)
		{
			node *root = head;
			if (root == NULL) 
			{
				head = new node(val,id,NULL);
				return;
			}
			while (1)
			{
				if (val < root->val)
					if (root->son[0]) root = root->son[0];
					else
					{
						root->son[0] = new node(val,id,root);
						splay(root->son[0]);
						break;
					}
				else
				{
					if (root->son[1]) root = root->son[1];
					else 
					{
						root->son[1] = new node(val, id, root);
						splay(root->son[1]);
						break;
					}
				}
			}
		}

		int find_kth(int val)
		{
			node *root = head;
			while(1)
			{
				if (!root) return -1; 
				if ((!root->son[0] && val == 1) || (root->son[0] && root->son[0]->size + 1 == val)) 
					return root->id;
				if (root->son[0] && root->son[0]->size >= val)
					root = root->son[0];
				else 
				{
					if (root->son[0]) 
					    val -= root->son[0]->size;
					val--;
					root = root->son[1];
				}
			}
		}
		friend void merge(Splay &a, Splay &b);
		friend void del(node *root, Splay &x);
    }island[MAXN];

    void del(Splay::node *root, Splay &x)
    {
		x.insert(root->val, root->id);
		if (root->son[0]) del(root->son[0], x);
		if (root->son[1]) del(root->son[1], x);
		delete root;
    }

    void merge(Splay &a, Splay &b)
    {
		if (a.head->size > b.head->size) swap(a, b);
		del(a.head, b);
		a.head = NULL;
    }

    int find(int x)
    {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    
    void connect(int u,int v)
    {
    	int fu = find(u),fv = find(v);
		if (fu == fv) return;
		fa[fu] = fv;
		merge(island[fu], island[fv]);
    }

    void work()
    {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) 
		{
			scanf("%d", &rank[i]);
			fa[i] = i;
			island[i].insert(rank[i], i);
		}	
		int u,v;
		for (int i = 1; i <= m; i++)
		{
			scanf("%d%d", &u, &v);
			connect(u,v); 
		}
		scanf("%d", &q);
		char c[5];
		int a,b;
		while(q--)
		{
			scanf("%s%d%d", c, &a, &b);
			if(c[0] == 'B') connect(a, b);
			else printf("%d\n", island[find(a)].find_kth(b));
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
