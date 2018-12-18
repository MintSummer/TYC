#include<bits/stdc++.h>
using namespace std;
const int MAXN=510;
int n,s,mx,cnt,dis[MAXN],Head[MAXN],vis[MAXN];
long long ans;

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<'9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct edge
{
    int to,next,w;
}E[MAXN];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].w=w;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

void dfs(int u)
{
    vis[u]=1;
    dis[u]=0;//dis[i]表示从点i开始，到距离它最远的子节点的距离
    int v,son=0;
    for(int i=Head[u];i;i=E[i].next)
    {
		v=E[i].to;
		if(vis[v]) continue;
		dfs(v);
		if(dis[v]+E[i].w>dis[u])//字节点+当前边值比dis[i]大时，更新
		{
			ans+=(dis[v]+E[i].w-dis[u])*son;//之前所有的儿子节点都要加上(dis[v]+E[i].w)
			dis[u]=dis[v]+E[i].w;
		}
		else ans+=dis[u]-dis[v]-E[i].w;//当前到儿子节点v的距离不够
		son++;
    }
}

int main()
{
    n=read(),s=read();
    int u,v,w;
    for(int i=1;i<n;i++)
    {
		u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
    }
    dfs(s);
    printf("%lld",ans);
    return 0;
}
