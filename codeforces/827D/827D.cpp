#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=2e5+10,inf=0x3f3f3f3f;
	int n,m,cnt,ffa[N],Head[N],Ans[N],mark[N],fa[N][20],mx[N][20],dep[N],mn[N][20];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void write(int x)
	{
		static int bask[15];
		int len=0;
		if(x<0) x=-x,putchar('-');
		if(!x) putchar('0');
		else
		{
			while(x) bask[++len]=x%10,x/=10;
			for(int i=len;i;i--) putchar('0'+bask[i]);
		}
	}
	
	struct Edge
	{
		int u,v,w,id,tag;
		bool operator < (const Edge &t) const
		{
			return w<t.w;
		}
	}e[N];
	
	int find(int x)
	{
		return x==ffa[x]?x:ffa[x]=find(ffa[x]);
	}
	
	struct edge
	{
		int to,next,w;
	}E[N<<1];
	
	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],w};
		Head[v]=cnt;
	}
	
	void kruskal()
	{
		sort(e+1,e+1+m);
		for(int i=1;i<=n;i++) ffa[i]=i;
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v;
			int fu=find(u),fv=find(v);
			if(fu==fv) continue;
			ffa[fu]=fv;
			e[i].tag=1;
			add(u,v,e[i].w);
		}
	}
	
	void dfs(int u)
	{
		dep[u]=dep[fa[u][0]]+1;
		for(int i=1;fa[u][i-1]&&i<=18;i++)
		{
			fa[u][i]=fa[fa[u][i-1]][i-1];
			mx[u][i]=max(mx[u][i-1],mx[fa[u][i-1]][i-1]);
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u][0]) continue;
			fa[v][0]=u;
			mx[v][0]=E[i].w;
			dfs(v);
		}
	}
	
	int get_mx(int u,int v)
	{
		int ans=0;
		if(dep[u]<dep[v]) swap(u,v);
		for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
			if(d&1)
				ans=max(ans,mx[u][t]),u=fa[u][t];
		if(u==v) return ans;
		for(int i=18;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
			{
				ans=max(ans,max(mx[u][i],mx[v][i]));
				u=fa[u][i],v=fa[v][i];
			}
		return max(ans,max(mx[u][0],mx[v][0]));
	}
	
	void update(int u,int v,int w)
	{
		if(dep[u]<dep[v]) swap(u,v);
		for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
			if(d&1)
			{
				mn[u][t]=min(mn[u][t],w);
				u=fa[u][t];
			}
		if(u==v) return;
		for(int i=18;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
			{
				mn[u][i]=min(mn[u][i],w);
				mn[v][i]=min(mn[v][i],w);
				u=fa[u][i],v=fa[v][i];
			}
		mn[u][0]=min(mn[u][0],w);
		mn[v][0]=min(mn[v][0],w);
	}
	
	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
			e[i]=(Edge){read(),read(),read(),i};
		kruskal();
		for(int i=1;i<=n;i++)
		{
			int f=find(i);
			if(!mark[f]) dfs(f),mark[f]=1;
		}
		memset(mn,inf,sizeof(mn));
		memset(Ans,inf,sizeof(Ans));
  		for(int i=1;i<=m;i++)
			if(!e[i].tag)
			{
				Ans[e[i].id]=get_mx(e[i].u,e[i].v);
				update(e[i].u,e[i].v,e[i].w);
			}
		for(int j=18;j>=0;j--)
			for(int i=1;i<=n;i++)
			{
				mn[i][j]=min(mn[i][j],mn[i][j+1]);
				mn[fa[i][j]][j]=min(mn[fa[i][j]][j],mn[i][j+1]);
			}
		for(int i=1;i<=m;i++)
			if(e[i].tag)
			{
				int u=e[i].u,v=e[i].v;
				if(u==fa[v][0]) Ans[e[i].id]=mn[v][0];
				else Ans[e[i].id]=mn[u][0];
			}
		for(int i=1;i<=m;i++)
		{
			if(Ans[i]>=inf) Ans[i]=-1;
			else Ans[i]--;
			write(Ans[i]),putchar(' ');
		}
	}
}

int main()
{
	//freopen("a.in","r",stdin);
	//freopen("tyc.out","w",stdout);
	TYC::work();
	return 0;
}
