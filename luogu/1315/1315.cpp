#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=10010,inf=0x3f3f3f3f;
    int n,m,k,s,t,cnt=1,D[N],mx[N],arrive[N],Head[N],down[N],pre[N],dis[N],vis[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct passenger
    {
        int tim,s,t;
    }a[N];

    struct edge
    {
        int to,next,w,c;
    }E[N<<3];

    inline void insert(int u,int v,int w,int c)
    {
        E[++cnt]=(edge){v,Head[u],w,c};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],0,-c};
        Head[v]=cnt;
    }

    bool spfa()
    {
        memset(pre,0,sizeof(pre));
        memset(dis,inf,sizeof(dis));
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
                if(E[i].w&&dis[v]>dis[u]+E[i].c)
                {
                    dis[v]=dis[u]+E[i].c;
                    pre[v]=i;
                    if(!vis[v]) q.push(v);
                }
            }
        }
        return dis[t]!=inf;
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
        n=read(),m=read(),k=read();
        for(int i=1;i<n;i++) D[i]=read();
        for(int i=1;i<=m;i++)
        {
            a[i].tim=read(),a[i].s=read(),a[i].t=read();
            mx[a[i].s]=max(mx[a[i].s],a[i].tim);
            down[a[i].t]++;
        }
        int ans=0;
        for(int i=1;i<n;i++) 
            arrive[i+1]=max(arrive[i],mx[i])+D[i];
        for(int i=1;i<=m;i++)
            ans+=arrive[a[i].t]-a[i].tim;
        s=(n<<1)+1,t=s+2;
        int s1=s+1;
        insert(s,s1,k,0);
        for(int i=1;i<n;i++)
        {
            insert(s1,i+n,D[i],0);
            insert(i,i+n,max(arrive[i]-mx[i],0),0);
            insert(i+n,i+1,inf,-down[i+1]);
            insert(i+1,t,inf,0);
        }
        printf("%d\n",ans+mcmf());
    }
}

int main()
{
    TYC::work();
    return 0;
}