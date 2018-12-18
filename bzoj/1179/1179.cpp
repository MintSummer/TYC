#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
 
namespace TYC
{
    typedef long long ll;
    const int MAXN=500010;
    int N,M,S,P,cnt,tim,top,tot;
    int Head[MAXN],money[MAXN],vis[MAXN],dfn[MAXN],low[MAXN],in[MAXN],st[MAXN],belong[MAXN],h[MAXN];
    ll ans,dis[MAXN],w[MAXN];
    vector<int> G[MAXN];
 
    int read()
    {
        int x=0;char ch=getchar();
        while(!isdigit(ch)) x=(ch=='-'?-x:x),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return x;
    }
 
    struct edge
    {
        int to,next;
    }E[MAXN];
 
    void add(int u,int v)
    {
        cnt++;
        E[cnt].to=v;
        E[cnt].next=Head[u];
        Head[u]=cnt;
    }
 
    struct Edge
    {
        int to,next;
    }e[MAXN*8];
 
    void adde(int u,int v)
    {
        cnt++;
        e[cnt].to=v;
        e[cnt].next=h[u];
        h[u]=cnt;
    }
 
    void Tarjan(int u)
    {
        dfn[u]=low[u]=++tim;
        st[++top]=u;
        in[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(!dfn[v])
            {
                Tarjan(v);
                low[u]=min(low[u],low[v]);
            }
            else
                if(in[v]) low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u])
        {
            tot++;
            int x;
            do
            {
                x=st[top--];
                belong[x]=tot;
                G[tot].push_back(x);
                in[x]=0;
                w[tot]+=money[x];
            }
            while(x!=u);
        }
    }
 
    void build()
    {
        cnt=0;
        for(int u=1;u<=N;u++)
            for(int i=Head[u];i;i=E[i].next)
            {
            int v=E[i].to;
            if(belong[u]!=belong[v])
                adde(belong[u],belong[v]);
            }
         
    }
 
    void spfa()
    {
        queue<int> q;
        q.push(S);
        dis[S]=w[S];
        vis[S]=1;
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(int i=h[u];i;i=e[i].next)
            {
                int v=e[i].to;
                if(dis[v]<dis[u]+w[v])
                {
                    dis[v]=dis[u]+w[v];
                    if(!vis[v]) vis[v]=1,q.push(v);
                }
            }
        }
    }
 
    void work()
    {
        N=read(),M=read();
        int u,v;
        for(int i=1;i<=M;i++)
        {
            u=read(),v=read();
            add(u,v);
        }
        for(int i=1;i<=N;i++) money[i]=read();
        cin>>S>>P;
        for(int i=1;i<=N;i++)
            if(!dfn[i]) Tarjan(i);
        S=belong[S];
        build();
        spfa();
        ll ans=0;
        for(int i=1;i<=P;i++) 
            ans=max(ans,dis[belong[read()]]);
        cout<<ans;
    }
}
 
int main()
{
    freopen("1179.in","r",stdin);
    TYC::work();
    return 0;
}
