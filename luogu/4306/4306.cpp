#include<bits/stdc++.h>
using namespace std;
const int MAXN=2010;
char ch[MAXN];
bitset<MAXN> f[MAXN];
int n,cnt,num,tot,top,Head[MAXN],h[MAXN],to[MAXN],hav[MAXN];
int dfn[MAXN],low[MAXN],st[MAXN],belong[MAXN],size[MAXN];
bool vis[MAXN],viss[MAXN][MAXN];
queue<int> q;
 
struct edge
{
    int to,next;
}E[MAXN*MAXN],e[MAXN*MAXN];
 
void add1(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}
 
void add2(int u,int v)
{
    cnt++;
    e[cnt].to=v;
    e[cnt].next=h[u];
    h[u]=cnt;
    to[v]++;
}
 
void Tarjan(int u)
{
    dfn[u]=low[u]=++num;
    st[++top]=u;
    vis[u]=1;
    for(int i=Head[u];i;i=E[i].next)
    {
		int v=E[i].to;
		if(!dfn[v]) Tarjan(v),low[u]=min(low[v],low[u]);
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
		    size[tot]++;
		}
		while(x!=u);
    }
}
 
void rebuild()
{
    cnt=0;
    for(int u=1;u<=n;u++)
		for(int i=Head[u];i;i=E[i].next)
		    if(belong[u]!=belong[E[i].to]&&!viss[belong[u]][belong[E[i].to]])
		    {
				add2(belong[u],belong[E[i].to]);
				viss[belong[u]][belong[E[i].to]]=1;
		    }
}
 
void solve()
{
    for(int i=1;i<=tot;i++) f[i][i]=1;
    for(int i=1;i<=tot;i++)
    if(!to[i]) q.push(i);
    int u,v;
    while(!q.empty())
    {
		u=q.front(),q.pop();
		for(int i=h[u];i;i=e[i].next)
		{
		    v=e[i].to;
		    f[v]=f[v]|f[u];
		    to[v]--;
		    if(!to[v]) q.push(v);
		}
    }
 
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
		scanf("%s",ch);
		for(int j=1;j<=n;j++)
		    if(i!=j&&ch[j-1]=='1') add1(i,j);
    }
    for(int i=1;i<=n;i++)
   		if(!dfn[i]) Tarjan(i);
    rebuild();
    solve();
    int ans=0;
    for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
		    if(f[i][j]) ans+=(size[i]*size[j]);
    printf("%d",ans);
    return 0;
}
