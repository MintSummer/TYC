#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=220,inf=0x3f3f3f3f;
    int m,n,s,t,cnt=1,Head[N],dis[N],pre[N],vis[N];
    
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

    ll mcmf(int d)
    {
        ll ans=0;
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


    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void work()
    {
		m=read(),n=read();
		s=n+m+1,t=n+m+2;
		for(int i=1;i<=m;i++) insert(s,i,read(),0);
		for(int i=1;i<=n;i++) insert(i+m,t,read(),0);
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				insert(i,j+m,inf,read());
		printf("%lld\n",mcmf(1));
		for(int i=2;i<=cnt;i+=2)
			E[i].w=E[i].w+E[i^1].w,E[i^1].w=0;
		printf("%lld\n",mcmf(-1));
    }
}

int main()
{
    TYC::work();
    return 0;
}
