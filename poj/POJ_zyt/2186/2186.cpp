#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,dfn[10010],low[10010],cnt,top,stack[10010],num;
int belong[10010],sizee[10010],out[10010];
bool vis[10010],viss[10010][10010];
vector<int>g[10010];
void tarjan(int x)
{
	stack[top++]=x;
	dfn[x]=low[x]=cnt++;
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(!vis[v])
		{
			if(low[v]==-1)
			{
				tarjan(v);
				low[x]=min(low[x],low[v]);
			}
			else
				low[x]=min(low[x],dfn[v]);
		}
	}
	if(dfn[x]==low[x])
	{
		int t;
		do
		{
			t=stack[--top];
			belong[t]=num;
			vis[t]=true;
			sizee[num]++;
		}while(t!=x);
		num++;
	}
}
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		g[a].push_back(b);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			memset(dfn,-1,sizeof(dfn));
			memset(low,-1,sizeof(dfn));
			cnt=top=0;
			tarjan(i);
		}
	for(int i=1;i<=n;i++)
	{
		int now=belong[i];
		for(int j=0;j<g[i].size();j++)
		{
			int a=belong[g[i][j]];
			if(a==now)continue;
			if(!viss[now][a])out[now]++,viss[now][a]=true;
		}
	}
	int ans=0;
	for(int i=0;i<num;i++)
	{
		if(out[i]==0)
			if(ans==0)
				ans=sizee[i];
			else
			{
				printf("0");
				return 0;
			}
	}
	printf("%d",ans);
	return 0;
}
