#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1010;

	int n,m,cnt,s,t,Head[N],dep[N],cur[N];
	bool mark[N<<2],vis[N];

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
	}E[10010];

	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0};
		Head[v]=cnt;
	}

	struct Edge	
	{
		int u,v,a,b;
	}e[2010];

	bool bfs()
	{
		queue<int> q;
		memset(dep,0,sizeof(int[n+5]));
		memcpy(cur,Head,sizeof(int[n+5]));
		dep[s]=1;
		q.push(s);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&!dep[v])
					dep[v]=dep[u]+1,q.push(v);
			}
		}
		return dep[t];
	}

	int dfs(int u,int mn)
	{
		if(u==t) return mn;
		int v,w,used=0;
		for(int &i=cur[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(E[i].w&&dep[v]==dep[u]+1)
			{
				w=dfs(v,min(mn-used,E[i].w));
				used+=w;
				E[i].w-=w,E[i^1].w+=w;
				if(used==mn) return used;
			}
		}
		if(!used) dep[u]=-1;
		return used;
	}

	inline int Dinic()
	{
		int ans=0;
		while(bfs()) ans+=dfs(s,0x3f3f3f3f);
		return ans;
	}

	bool check(int mid)
	{
		static int deg[N];
		cnt=1;
		memset(Head,0,sizeof(int[n+5]));
		memset(deg,0,sizeof(int[n+5]));
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v;
			if(e[i].a<=mid)
			{ 
				deg[u]--,deg[v]++;
				if(e[i].b<=mid) add(v,u,1);
			}
			else if(e[i].b<=mid)
				deg[u]++,deg[v]--;
		}	
		int tot=0;
		for(int i=1;i<=n;i++)
		{
			if(deg[i]%2!=0) return false;
			if(deg[i]>0) add(s,i,deg[i]/2),tot+=deg[i]/2;
			else if(deg[i]<0) add(i,t,-deg[i]/2);
		}
		return Dinic()==tot;
	}

	void work()
	{
		n=read(),m=read();
		int mn=0x3f3f3f3f,mx=0;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),a=read(),b=read();
			e[i]=(Edge){u,v,a,b};
			mn=min(mn,min(a,b));
			mx=max(mx,max(a,b));
		}
		s=n+1,t=s+1;
		int l=mn,r=mx,mid,ans=-1;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans==-1) puts("NIE");
		else printf("%d\n",l);
	}
}

int main()
{
	freopen("2095.in","r",stdin);
	freopen("2095.out","w",stdout);
	TYC::work();
	return 0;
}
