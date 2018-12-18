#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f,N=3010;
    int tot,s,t,cnt=1,flow,ans,len;
    int path[N],f[N*N*2],G[110][110],num[110][110],Head[N],dis[N],vis[N],pre[N];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int from,to,next,w,c;
    }E[N*N*2];

    inline void insert(int u,int v,int w,int c)
    {
		E[++cnt]=(edge){u,v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){v,u,Head[v],0,-c};
		Head[v]=cnt;
    }

    bool spfa()
    {
		memset(pre,0,sizeof(pre));
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=t;i++) dis[i]=-inf;
		queue<int> q;
		q.push(s);
		dis[s]=0,vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			vis[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dis[v]<dis[u]+E[i].c)
				{
					dis[v]=dis[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return dis[t]!=-inf;
    }

    void mcmf()
    {
		ans=0,flow=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i].from])
				mn=min(mn,E[i].w);
			for(int i=pre[t];i;i=pre[E[i].from])
				E[i].w-=mn,E[i^1].w+=mn;
			ans+=mn*dis[t],flow+=mn;
		}
    }

    void dfs(int x,int y)
    {
		for(int i=Head[num[x][y]+tot];i;i=E[i].next)
		{
			if(f[i]>=E[i^1].w) continue;
			f[i]++;
			if(E[i].to==num[x+1][y])
			{
				path[++len]=0;
				dfs(x+1,y);
				return;
			}
			if(E[i].to==num[x][y+1])
			{
				path[++len]=1;
				dfs(x,y+1);
				return;
			}
		}
    }

    void work()
    {
		int k=read(),m=read(),n=read(),now=0;
		s=n*m*2+1,t=s+1;
		tot=n*m;
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=m;j++)
			{
				G[i][j]=read();
				num[i][j]=++now;
				if(G[i][j]==1) continue;
				if(G[i][j]==2) insert(num[i][j],num[i][j]+tot,1,1);
				insert(num[i][j],num[i][j]+tot,inf,0);
			}
		if(G[1][1]!=1) insert(s,1,k,0);
		if(G[n][m]!=1) insert(num[n][m]+tot,t,k,0);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(G[i][j]==1) continue;
				if(G[i+1][j]!=1&&i!=n) insert(num[i][j]+tot,num[i+1][j],inf,0);
				if(G[i][j+1]!=1&&j!=m) insert(num[i][j]+tot,num[i][j+1],inf,0);
			}
		mcmf();
		for(int i=1;i<=flow;i++)
		{
			len=0;
			dfs(1,1);
			for(int j=1;j<=len;j++) printf("%d %d\n",i,path[j]);
		}
    }
    
}

int main()
{
    TYC::work();
    return 0;
}
