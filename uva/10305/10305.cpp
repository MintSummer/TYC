#include<bits/stdc++.h>
using namespace std;
int n,m,Head[110],cnt,in[110],vis[110],dfn[110],top;
//vis[i]==0还未访问、vis[i]==1已经访问过了 
//vis[i]==-1表示正在访问的路径上有i这个点，并且还没有递归回到i 
//注意：一个图如果有环，就一定不存在拓扑排序，只有有向无环图才有拓扑序 
//判环这个真是…… 

struct edge
{
	int to,next;
}E[10010];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

bool dfs(int u)
{
	vis[u]=-1;
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(vis[v]==-1) return false;//正在访问的路径上有v但未递归回去，说明有环 
		if(!vis[v]&&!dfs(v)) return false;
  	}
  	vis[u]=1;
  	dfn[top--]=u;
  	return true;
}

bool huan()
{
	top=n;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!vis[i]&&!dfs(i)) return false;
	return true; 
}

int main()
{
	while(scanf("%d%d",&n,&m)&&(n||m))//只有n==0&&m==0时才结束 
	{
		cnt=0;
		memset(Head,0,sizeof(Head));
		int u,v;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			add(u,v),in[v]++;
		}
		if(huan())
			for(int i=1;i<=n;i++) printf("%d ",dfn[i]);
		else printf("No");
		printf("\n");
	}
	return 0;
} 
