#include<bits/stdc++.h>
using namespace std;
const int MAXN=410;
const int inf=0x3f3f3f3f;
int n,cnt=1,s,t,Head[MAXN],dep[MAXN],cur[MAXN];

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct edge
{
    int to,next,w;
}E[MAXN*MAXN*2];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].w=w;
    Head[u]=cnt;
}

void insert(int u,int v)
{
    add(u,v,1),add(v,u,0);
}

bool bfs()
{
    queue<int> q;
    memset(dep,-1,sizeof(dep));
    memcpy(cur,Head,sizeof(cur));
    dep[s]=0;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(dep[v]==-1&&E[i].w)
            dep[v]=dep[u]+1,q.push(v);
        }
    }
    return dep[t]!=-1;
}

int dfs(int u,int mn)
{
    if(u==t) return mn;
    int v,w,used=0;
    for(int &i=cur[u];i;i=E[i].next)
    {
        v=E[i].to;
        if(dep[v]==dep[u]+1&&E[i].w)
        {
            w=dfs(v,min(mn,E[i].w));
            used+=w;
            E[i].w-=w,E[i^1].w+=w;
            if(used==mn) return used;
        }
    }
    if(!used) dep[u]=-1;
    return used;
}

int Dinic()
{
    int ans=0;
    while(bfs())
        ans+=dfs(s,inf);
    return ans;
}

int main()
{
    int T=read();
    while(T--)
    {
        memset(Head,0,sizeof(Head));
        n=read();
        s=0,t=2*n+1;
        for(int i=1;i<=n;i++)
            insert(s,i),insert(i+n,t);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            if(read()) insert(i,j+n);
        if(Dinic()==n) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
