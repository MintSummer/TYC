#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=200010;

	int cnt,node,Head[N],h[N],size[N],son[N],top[N],fa[N],dep[N],val[N];
	vector<int> G[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}

	struct edge
	{
		int to,next;
	}E[N<<1],e[N<<1];

	inline void add(int *H,edge *ed,const int u,const int v)
	{
		ed[++cnt]=(edge){v,H[u]};
		H[u]=cnt;
		ed[++cnt]=(edge){u,H[v]};
		H[v]=cnt;
	}

	void Tarjan(const int u,const int pre)
	{
		static int tim,top,bel[N],dfn[N],low[N];
		static pa sta[N<<1];
		dfn[u]=low[u]=++tim;
		for(int i=h[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if((i^1)==pre) continue;
			if(dfn[v]) low[u]=min(low[u],dfn[v]);
			else
			{
				sta[++top]=pa(u,v);
				Tarjan(v,i);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u])
				{
					node++;
					int x,y;
					do
					{
						x=sta[top].first,y=sta[top].second,top--;
						if(bel[x]!=node) bel[x]=node,add(Head,E,node,x);
						if(bel[y]!=node) bel[y]=node,add(Head,E,node,y);
					}
					while(x!=u&&y!=v);
				}
			}
		}
	}

	void dfs(const int u)
	{
		size[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			fa[v]=u,dep[v]=dep[u]+1;
			dfs(v);
			size[u]+=size[v];
			if(size[v]>size[son[u]]) son[u]=v;
		}
	}

	void dfs(const int u,const int ance)
	{
		top[u]=ance;
		if(son[u]) dfs(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]||v==son[u]) continue;
			dfs(v,v);
		}
	}

	inline int LCA(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	}

	void search(const int u)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			search(v);
			val[u]+=val[v];
		}
	}

	void work()
	{
		int n=read(),m=read(),q=read();
		node=n,cnt=1;
		while(m--)
		{
			int u=read(),v=read();
			add(h,e,u,v);
		}
		cnt=0;
		Tarjan(1,0);
		dfs(1);
		dfs(1,1);
		while(q--)
		{
			int u=read(),v=read(),lca=LCA(u,v);
			val[u]++,val[v]++;
			val[lca]--,val[fa[lca]]--;
		}
		search(1);
		for(int i=1;i<=n;i++) write(val[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
