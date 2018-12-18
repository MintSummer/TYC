#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=3e5+10;
	int n,m,cnt,tot,mxlen,res,Head[N],size[N],dis[N],dep[N],vis[N],fa[N],son[N],top[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int to,next,w;
	}E[N<<1];

	void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	struct ques
	{
		int u,v,lca,len;
	}q[N];

	void dfs1(int u)
	{
		int hs=0;
		size[u]=1;
		dep[u]=dep[fa[u]]+1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			fa[v]=u;
			dis[v]=dis[u]+E[i].w;
			dfs1(v);
			size[u]+=size[v];
			if(size[v]>size[hs]) hs=v;
		}
		son[u]=hs;
	}
	
	void dfs2(int u,int ance)
	{
		top[u]=ance;
		if(son[u]) dfs2(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]||v==son[u]) continue;
			dfs2(v,v);
		}
	}
	
	int LCA(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	}

	void dfs3(int u,int pre)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			dfs3(v,i);
			vis[u]+=vis[v];
		}
		if(vis[u]==tot) res=max(res,E[pre].w);
	}

	inline bool check(int x)
	{
		tot=res=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=m;i++)
			if(q[i].len>x)
			{
				tot++;
				vis[q[i].u]++,vis[q[i].v]++;
				vis[q[i].lca]-=2;
			}
		dfs3(1,0);
		return mxlen-res<=x;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,w);
		}
		dfs1(1);
		dfs2(1,0);
		for(int i=1;i<=m;i++) 
		{
			int u=read(),v=read();
			q[i].u=u,q[i].v=v;
			q[i].lca=LCA(u,v);
			q[i].len=dis[u]+dis[v]-dis[q[i].lca]*2;
			mxlen=max(mxlen,q[i].len);
		}
		int l=0,r=mxlen,mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
