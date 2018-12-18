#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=60,M=6100,inf=0x3f3f3f3f;
    int s,t,cnt=1,num[N][N],Head[M],dis[M],pre[M],vis[M];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next,w,c;
    }E[M*200];
    
    inline void add(int u,int v,int w,int c)
    {
        E[++cnt]=(edge){v,Head[u],w,c};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],0,-c};
        Head[v]=cnt;
    }

    bool spfa()
    {
        memset(pre,0,sizeof(pre));
		for(int i=1;i<=t;i++) dis[i]=-inf;
        queue<int> q;
        dis[s]=0;
        q.push(s);
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
                    if(!vis[v]) q.push(v),vis[v]=1;
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
            for(int i=pre[t];i;i=pre[E[i^1].to])
                mn=min(mn,E[i].w);
            for(int i=pre[t];i;i=pre[E[i^1].to])
                E[i].w-=mn,E[i^1].w+=mn;
            ans+=mn*dis[t];
        }
        return ans;
    }

    void work()
    {
        
        int n=read(),m=read(),tot=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                num[i][j]=++tot;
        s=(tot<<1)+1,t=s+1;
        add(s,num[1][1],2,0);
        add(num[n][m]+tot,t,2,0);
		add(num[1][1],num[1][1]+tot,inf,0);
		add(num[n][m],num[n][m]+tot,inf,0);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                int x=read();
                if(num[i][j]!=1&&num[i][j]!=tot) 
					add(num[i][j],num[i][j]+tot,1,x);
                if(i<n) add(num[i][j]+tot,num[i+1][j],inf,0);
                if(j<m) add(num[i][j]+tot,num[i][j+1],inf,0);
            }
        printf("%d\n",mcmf());
    }    
}

int main()
{
	freopen("a.in","r",stdin);
    TYC::work();
    return 0;
}
