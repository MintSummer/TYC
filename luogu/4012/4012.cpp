#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=310,inf=0x3f3f3f3f;
    int n,m,a,b,s,t,cnt=1,num[20][20],Head[N],pre[N],vis[N],dis[N];

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

    void insert(int u,int v,int w,int c)
    {
		E[++cnt]=(edge){u,v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){v,u,Head[v],0,-c};
		Head[v]=cnt;
    }

    bool spfa()
    {
		for(int i=0;i<=t;i++) dis[i]=-inf;
		memset(pre,0,sizeof(pre));
		memset(vis,0,sizeof(vis));
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
				if(E[i].w>0&&dis[v]<dis[u]+E[i].c)
				{
					dis[v]=dis[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return dis[t]!=-inf;
    }

    int mcmf()
    {
		int ans=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i].from])
				mn=min(mn,E[i].w);
			for(int i=pre[t];i;i=pre[E[i].from])
				E[i].w-=mn,E[i^1].w+=mn;
			ans+=dis[t]*mn;
		}
		return ans;
    }

    void work()
    {
		a=read(),b=read();
		m=read(),n=read();
		int k,x,y,tot=0;
		for(int i=0;i<=m;i++) 
			for(int j=0;j<=n;j++)
				num[i][j]=++tot;
		for(int i=0;i<=m;i++)
			for(int j=0;j<n;j++)
			{
				x=read();
				insert(num[i][j],num[i][j+1],1,x);//先到的机器人拿到了
				insert(num[i][j],num[i][j+1],inf,0);//后面的机器人还可以过,所以还要有流
			}
		for(int i=0;i<=n;i++)
			for(int j=0;j<m;j++)
			{
				x=read();
				insert(num[j][i],num[j+1][i],1,x);
				insert(num[j][i],num[j+1][i],inf,0);
			}
		s=++tot,t=s+1;
		for(int i=1;i<=a;i++)
		{
			k=read(),x=read(),y=read();
			insert(s,num[x][y],k,0);
		}
		for(int i=1;i<=b;i++) 
		{
			k=read(),x=read(),y=read();
			insert(num[x][y],t,k,0);
		}
		printf("%d\n",mcmf());
    }
}

int main()
{
    TYC::work();
    return 0;
}
