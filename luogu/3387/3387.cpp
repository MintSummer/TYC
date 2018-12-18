#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e4+10;
int n,m,cnt,Head[MAXN],val[MAXN],in[MAXN];
int tim,dfn[MAXN],low[MAXN],belong[MAXN],vis[MAXN],st[MAXN],top,tot;
ll V[MAXN],dp[MAXN],ans;
queue<int> q;

struct edge
{
    int to,next;
}E[100010];

void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

int h[MAXN],cnte;
struct Edge
{
    int to,next;
}e[100010];

void adde(int u,int v)
{
    cnte++;
    e[cnte].to=v;
    e[cnte].next=h[u];
    h[u]=cnte;
}

void Tarjan(int u)
{
    low[u]=dfn[u]=++tim;
    st[++top]=u;
    vis[u]=1;
    for(int i=Head[u];i;i=E[i].next)
    {
        int v=E[i].to;
        if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
        else if(vis[v]) low[u]=min(low[u],dfn[v]);
    }

    if(dfn[u]==low[u])
    {
        tot++;
        int x;
        do
        {
            x=st[top--];
            vis[x]=0;
            belong[x]=tot;
            V[tot]+=val[x];
        }
        while(x!=u);
    }
}

void build()
{
    for(int i=1;i<=n;i++)
        for(int j=Head[i];j;j=E[j].next)
            if(belong[i]!=belong[E[j].to])
            	in[belong[E[j].to]]++,adde(belong[i],belong[E[j].to]);	
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    int u,v;
    for(int i=1;i<=m;i++) 
        scanf("%d%d",&u,&v),add(u,v);
        
    for(int i=1;i<=n;i++)
    	if(!dfn[i]) Tarjan(i);
    build();
    
    for(int i=1;i<=tot;i++) 
        if(!in[i]) q.push(i),dp[i]=V[i];
    while(!q.empty())
    {
    	int u=q.front();q.pop();
    	for(int i=h[u];i;i=e[i].next)
    	{
    		int v=e[i].to;
    		dp[v]=max(dp[v],dp[u]+V[v]);
    		in[v]--;
    		if(!in[v]) q.push(v);
        }
    }
    for(int i=1;i<=tot;i++) ans=max(ans,dp[i]);
    printf("%lld",ans);
    return 0;
}


