#include<bits/stdc++.h>
using namespace std;
const int MAXN=310;
int n,cnt,tot,Head[MAXN],fa[MAXN],vis[MAXN];

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

void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

bool Path(int u)
{
    for(int i=Head[u];i;i=E[i].next)
    {
        int v=E[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(fa[v]==-1||Path(fa[v])) 
        {
            fa[v]=u;
            return true;
        }
    }
    return false;
}

bool Hungary()
{
    memset(fa,-1,sizeof(fa));
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if(!Path(i)) return false;
    }
    return true;
}

int main()
{
    int T=read();
    while(T--)
    {
        memset(Head,0,sizeof(Head));
        n=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            	if(read()) add(i,j);
        if(Hungary()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
