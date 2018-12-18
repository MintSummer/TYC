#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace Tree
{
	const int N=100000*20+10;
	int cnt,ls[N],rs[N],sum[N];

	void insert(int &root,int last,int l,int r,int val)
	{
		root=++cnt;
		sum[root]=sum[last]+1;
		ls[root]=ls[last],rs[root]=rs[last];
		if(l==r) return;
		int mid=(l+r)>>1;
		if(val<=mid) insert(ls[root],ls[last],l,mid,val);
		else insert(rs[root],rs[last],mid+1,r,val);
	}

	int query(int a,int b,int c,int d,int l,int r,int k)
	{
		if(l==r) return l;
		int res=sum[ls[a]]+sum[ls[b]]-sum[ls[c]]-sum[ls[d]];
		int mid=(l+r)>>1;
		if(k<=res) return query(ls[a],ls[b],ls[c],ls[d],l,mid,k);
		else return query(rs[a],rs[b],rs[c],rs[d],mid+1,r,k-res);
	}
}

namespace TYC
{
	const int N=100010;
	int n,m,cnt,tot,val[N],tmp[N],Head[N],dep[N],fa[N][20],root[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int to,next;
	}E[N<<1];

	void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	void dfs1(int u,int f)
	{
		dep[u]=dep[f]+1;
		fa[u][0]=f;
		for(int i=1;i<=18;i++)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs1(v,u);
		}
	}

	void dfs2(int u,int f)
	{
		Tree::insert(root[u],root[f],1,tot,val[u]);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs2(v,u);
		}
	}

	int lca(int u,int v)
	{
		if(dep[u]<dep[v]) swap(u,v);
		for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
			if(d&1) u=fa[u][t];
		if(u==v) return u;
		for(int i=18;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) val[i]=tmp[i]=read();
		sort(tmp+1,tmp+1+n);
		tot=unique(tmp+1,tmp+n+1)-tmp-1;
		for(int i=1;i<=n;i++) 
			val[i]=lower_bound(tmp+1,tmp+tot+1,val[i])-tmp;
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}	
		dfs1(1,0);
		dfs2(1,0);
		int ans=0,u,v,k;
		while(m--)
		{
			u=read(),v=read(),k=read();
			u^=ans;
			int x=lca(u,v);
			ans=tmp[Tree::query(root[u],root[v],root[x],root[fa[x][0]],1,tot,k)];
			printf("%d\n",ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
