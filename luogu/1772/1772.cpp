#include<bits/stdc++.h>
using namespace std;
int n,m,k,e,cnt,d;
int Head[110],flag[110][25];
long long dp[110][110],f[110],ans[110];
queue<int> q;
bool vis[25],clo[25];

struct edge
{
	int to,next,w;
}E[110*110];

void add(int u,int v,int w)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
}

int spfa(int s,int e)
{
	memset(vis,false,sizeof(vis));
	memset(clo,true,sizeof(clo));
	memset(f,0x3f3f3f3f,sizeof(f));
	for(int i=s;i<=e;i++)
		for(int j=1;j<=m;j++) 
			if(flag[i][j]) clo[j]=false;
	q.push(1);
	f[1]=0;
	vis[1]=1;
	int u,v;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(clo[v]&&f[v]>f[u]+E[i].w)
			{
				f[v]=f[u]+E[i].w;
				if(!vis[v]) vis[v]=1,q.push(v);
			}
		}
	}
	return f[m];
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&e);
	int u,v,w;
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}

	scanf("%d",&d);
	int a,b,p;
	for(int i=1;i<=d;i++)
	{
		scanf("%d%d%d",&p,&a,&b);
		for(int i=a;i<=b;i++) flag[i][p]=1;
	}

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) 
			dp[i][j]=spfa(i,j);
	//用dp[i][j]表示从i到j选取同一种路线的最短路
	for(int i=1;i<=n;i++)
	{
		ans[i]=dp[1][i]*i;
		for(int j=0;j<i;j++)
			ans[i]=min(ans[i],ans[j]+dp[j+1][i]*(i-j)+k);
	}
	printf("%lld",ans[n]);
	return 0;
}
