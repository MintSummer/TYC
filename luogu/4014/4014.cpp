#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=210,inf=0x3f3f3f3f;
    int n,s,t,cnt=1,Head[N],vis[N],pre[N],dis[N];
    
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

    bool spfa(int d)
    {
        for(int i=1;i<=t;i++) dis[i]=inf*d;
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
				if(!E[i].w) continue;
                if((d==1&&dis[v]>dis[u]+E[i].c)||(d==-1&&dis[v]<dis[u]+E[i].c))
                {
                    dis[v]=dis[u]+E[i].c;
                    pre[v]=i;
                    if(!vis[v]) vis[v]=1,q.push(v);
                }
            }
        }
        return dis[t]!=inf*d;
    }

    int mcmf(int d)
    {
        int ans=0;
        while(spfa(d))
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

    void work()
    {
		scanf("%d",&n);
		s=n*2+1,t=n*2+2;
		for(int i=1;i<=n;i++) insert(s,i,1,0);
		for(int i=1;i<=n;i++) insert(i+n,t,1,0);
		int x;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				scanf("%d",&x);
				insert(i,j+n,1,x);
			}
		printf("%d\n",mcmf(1));
		for(int i=2;i<=cnt;i+=2)
			E[i].w=1,E[i^1].w=0;
		printf("%d\n",mcmf(-1));
    }
}

int main()
{
    TYC::work();
    return 0;
}
