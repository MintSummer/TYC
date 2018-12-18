#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=1210,inf=0x3f3f3f3f;
    int n,m,cnt,s,t,tot,a[N],Head[N],dis[N],vis[N],pre[N];

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
		for(int i=1;i<=t;i++) dis[i]=-inf;
		memset(vis,0,sizeof(vis));
		memset(pre,0,sizeof(pre));
		queue<int> q;
		q.push(s);
		dis[s]=0,vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
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
			ans+=mn*dis[t];
		}
		return ans;
    }

    void init()
    {
		cnt=1;
		memset(Head,0,sizeof(Head));
    }

    void solve1()
    {
		init();
		s=tot*2+1,t=tot*2+2;
		for(int i=1;i<=m;i++) insert(s,i,1,0);
		for(int i=1;i<=tot;i++) insert(i,i+tot,1,0);
		for(int i=tot;i>tot-n-m;i--) insert(i+tot,t,1,a[i]);
		int tmp=0;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m+i;j++)
			{
				insert(j+tmp+tot,j+tmp+m+i-1,1,a[j+tmp]);
				insert(j+tmp+tot,j+tmp+m+i,1,a[j+tmp]);
			}
			tmp+=m+i-1;
		}
		printf("%d\n",mcmf());
    }

    void solve(int flow)//flow决定边是否可以多选
    {
		init();
		s=tot+1,t=tot+2;
		for(int i=1;i<=m;i++) insert(s,i,1,0);//只能有m个路径
		int tmp=0;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m+i;j++)
			{
				insert(j+tmp,j+tmp+m+i-1,flow,a[j+tmp]);
				insert(j+tmp,j+tmp+m+i,flow,a[j+tmp]);
			}
			tmp+=m+i-1;
		}
		for(int i=1;i<n+m;i++)
			insert(i+tmp,t,inf,a[i+tmp]);//点可以多选
		printf("%d\n",mcmf());
    }

    void work()
    {
		scanf("%d%d",&m,&n);
		tot=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<m+i;j++)
			scanf("%d",&a[j+tot]);
			tot+=m+i-1;
		}
		solve1();
		solve(1);
		solve(inf);
    }
}

int main()
{
    TYC::work();
    return 0;
}
