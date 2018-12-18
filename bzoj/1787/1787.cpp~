#include<bits/stdc++.h>
//求出两两lca，其中有两个相同，答案则为另一个 
using namespace std;
const int MAXN=500010;
int n,m,cnt;
int Head[MAXN],fa[MAXN][25],dep[MAXN],vis[MAXN];
 
struct edge
{
    int to,next;
}E[MAXN*2];
 
void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}
 
void dfs(int u,int f)
{
    vis[u]=1;
    dep[u]=dep[f]+1;
    fa[u][0]=f;
    for(int i=Head[u];i;i=E[i].next)
        if(!vis[E[i].to]&&E[i].to!=f) dfs(E[i].to,u);
}
 
void beizeng()
{
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            fa[i][j]=fa[fa[i][j-1]][j-1];
}
 
int lca(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    int d=dep[u]-dep[v],t=0;
    while(d)
    {
        if(d&1) u=fa[u][t];
        t++,d>>=1;
    }
    if(u==v) return u;
    for(int i=20;i>=0;i--)
        if(fa[u][i]!=fa[v][i])
            u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
 
int dis(int a,int b)
{
    int t=lca(a,b);
    return dep[a]+dep[b]-dep[t]*2;
}
 
int main()
{
    scanf("%d%d",&n,&m);
    int a,b,c;  
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }
    dfs(1,0);
    beizeng();
    while(m--)
    {
        scanf("%d%d%d",&a,&b,&c);
        int x=lca(a,b),y=lca(b,c),z=lca(a,c),t;
        if(x==y) t=z;
        else if(y==z) t=x;
        else t=y;
        printf("%d %d\n",t,dis(a,t)+dis(b,t)+dis(c,t));
    }
    return 0;
}
