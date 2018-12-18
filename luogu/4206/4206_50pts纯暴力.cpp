// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1010,inf=0x3f3f3f3f;
    int n,m,sc,sk,cnt,Head[N],deg[N],G[N][N];
    double ans;

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void search(int u,int k,int step,double p)
    {
        int to=-1;
        for(int i=Head[u];i;i=E[i].next)
        {   
            int v=E[i].to;
            if(to==-1||G[v][k]<G[to][k]||G[v][k]==G[to][k]&&v<to) to=v;
        }
        if(to==k) {ans+=p*step;return;}
        u=to,to=-1;
        for(int i=Head[u];i;i=E[i].next)
        {   
            int v=E[i].to;
            if(to==-1||G[v][k]<G[to][k]||G[v][k]==G[to][k]&&v<to) to=v;
        }
        if(to==k) {ans+=p*step;return;}
        search(to,k,step+1,p/(deg[k]+1));
        for(int i=Head[k];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==to) {ans+=(double)step*p/(deg[k]+1);continue;}
            search(to,v,step+1,p/(deg[k]+1));
        }
    }

    void work()
    {
        n=read(),m=read();
        sc=read(),sk=read();
        memset(G,inf,sizeof(G));
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
            deg[u]++,deg[v]++;
            G[u][v]=G[v][u]=1;
        }
        for(int i=1;i<=n;i++) G[i][i]=0;
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    if(G[i][j]>G[i][k]+G[k][j])
                        G[i][j]=G[i][k]+G[k][j];
        search(sc,sk,1,1.0);
        printf("%.3f",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}