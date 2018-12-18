#include<bits/stdc++.h>
using namespace std;
const int MAXN=100*2+10;
int n,m,cnt,ans,G[110][110],Head[MAXN],vis[MAXN],fa[MAXN];

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

struct edge
{
	int to,next;
}E[1010];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

void floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]|=(G[i][k]&G[k][j]);
}

void build()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(G[i][j]) add(i,n+j);
}

bool Path(int u,int tim)
{
	for(int i=Head[u];i;i=E[i].next)
	{
		int v=E[i].to;
		if(vis[v]==tim) continue;
		vis[v]=tim;//时间戳->不用每次都写memset了
		if(fa[v]==-1||Path(fa[v],tim)) 
		{
			fa[v]=u;
			return true;
		}
	}
	return false;
}

void Hungary()
{
	memset(fa,-1,sizeof(fa));
	ans=0;
	for(int i=1;i<=n;i++)
		if(Path(i,i)) ans++;
}

int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		G[u][v]=1;
	}
	floyd();
	build();
	Hungary();
	printf("%d",n-ans);
	return 0;
}
