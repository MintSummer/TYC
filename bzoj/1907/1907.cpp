#include<bits/stdc++.h>
using namespace std;
const int MAXN=10010;
int t,n,cnt;
int Head[MAXN],ans[MAXN];
bool vis[MAXN];

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

void init()
{
	cnt=0;
	memset(Head,0,sizeof(Head));
	memset(vis,false,sizeof(vis));
	memset(ans,0,sizeof(ans));
}

void dfs(int u,int f)
{
    ans[u]=vis[u]=1;
    int v,son=0;
    for(int i=Head[u];i;i=E[i].next)
    {
	v=E[i].to;
	if(v==f) continue;
	dfs(v,u);
	son+=vis[v];
	ans[u]+=ans[v];
    }
    if(son>=2) ans[u]-=2,vis[u]=0;
    else if(son) ans[u]--;
}

int main()
{
	int u,v;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		init();
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u);
		}
		dfs(1,0);
		printf("%d\n",ans[1]);
	}
	return 0;
}
