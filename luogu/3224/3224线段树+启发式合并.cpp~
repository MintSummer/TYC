#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;

namespace Tree
{
    int cnt,son[MAXN*20][2],num[MAXN*20],l[MAXN*20],r[MAXN*20];

    inline void update(int root)
    {
		num[root]=num[son[root][0]]+num[son[root][1]];
    }

    void build(int &root,int val,int lt,int rt)
    {
		root=++cnt;
		l[root]=lt,r[root]=rt;
		if(lt==rt) {num[root]=1;return;}
		int mid=(lt+rt)>>1;
		if(val<=mid) build(son[root][0],val,lt,mid);
		else build(son[root][1],val,mid+1,rt);
		update(root);
    }

    int merge(int root,int last)
    {
		if(!root) return last; 
		else if(!last) return root;
		if(num[root]<num[last]) swap(root,last);
		son[root][0]=merge(son[root][0],son[last][0]);
		son[root][1]=merge(son[root][1],son[last][1]);
		update(root);
		return root;
    }

    int ask(int root,int k)
    {
		if(num[root]<k) return -1;
		if(l[root]==r[root]) return l[root]; 
		if(num[son[root][0]]>=k) return ask(son[root][0],k);
		else return ask(son[root][1],k-num[son[root][0]]);
    }
}

namespace TYC
{
    int n,m,q,rank[MAXN],fa[MAXN],root[MAXN],id[MAXN];
    using namespace Tree;
    int find(int a)
    {
		return a==fa[a]?a:fa[a]=find(fa[a]);
    }

    inline void connect(int u,int v)
    {
		int fu=find(u),fv=find(v);
		if(fu==fv) return;
		fa[fv]=fu;
		root[u]=merge(root[fu],root[fv]);
    }

    void work()
    {
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&rank[i]);
			id[rank[i]]=i;
			build(root[i],rank[i],1,n);
			fa[i]=i;
		}
		int u,v;
		while(m--)
			scanf("%d%d",&u,&v),connect(u,v);
		scanf("%d",&q);
		char ch[5];
		while(q--)
		{
			scanf("%s%d%d",ch,&u,&v);
			if(ch[0]=='Q') 
			{
				int tmp=ask(root[find(u)],v);
				printf("%d\n",tmp==-1?-1:id[tmp]);
			}
			else connect(u,v);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
