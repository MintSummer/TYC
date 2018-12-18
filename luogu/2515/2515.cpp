#include<bits/stdc++.h>
using namespace std;
const int MAXN=110;
int n,m,cnt,num,Head[MAXN],w[MAXN],v[MAXN],d[MAXN],V[MAXN],W[MAXN],tot,S;
int dfn[MAXN],low[MAXN],vis[MAXN],belong[MAXN],st[MAXN],top,in[MAXN];
int dp[MAXN][1010];//树上背包，基本同01背包一样

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
    int to,next;
}E[MAXN*MAXN*2];

inline void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

void Tarjan(int u)
{
    st[++top]=u;
    dfn[u]=low[u]=++num;
    vis[u]=1;
    for(int i=Head[u];i;i=E[i].next)
    {
		int v=E[i].to;
		if(dfn[v])
			{if(vis[v]) low[u]=min(low[u],dfn[v]);}
		else Tarjan(v),low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
		tot++;
		int x;
		do
		{
			x=st[top--];
			W[tot]+=w[x],V[tot]+=v[x];
			belong[x]=tot;
			vis[x]=0;
		}
		while(x!=u);
    }
}

void build()
{
    S=0;
    cnt=0;
    memset(Head,0,sizeof(Head));
    for(int i=1;i<=n;i++)
    {
		int v=belong[i],u=belong[d[i]];
		if(u!=v&&d[i]) add(u,v),in[v]++;
    }
    for(int i=1;i<=tot;i++)
		if(!in[i]) add(S,i);
}

void dfs(int u)
{
    for(int i=W[u];i<=m;i++) dp[u][i]=V[u];
    int v;
    for(int i=Head[u];i;i=E[i].next)
    {
		v=E[i].to;
		dfs(v);
		for(int i=m;i>=W[u];i--)
			for(int j=0;j<=i-W[u];j++)
				dp[u][i]=max(dp[u][i],dp[u][i-j]+dp[v][j]);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) w[i]=read();
    for(int i=1;i<=n;i++) v[i]=read();
    for(int i=1;i<=n;i++)
    {
		d[i]=read();
		if(d[i]) add(d[i],i);
    }
    for(int i=1;i<=n;i++)
		if(!dfn[i]) Tarjan(i);
    build();
    dfs(S);
    printf("%d",dp[S][m]);
    return 0;
}
