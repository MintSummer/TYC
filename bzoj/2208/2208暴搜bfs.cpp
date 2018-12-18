#include<bits/stdc++.h>
using namespace std;
const int MAXN=2010;
int n;
int to[MAXN],vis[MAXN],G[MAXN][MAXN];
queue<int> q;

void read(int u)
{
	char ch[MAXN];
	int tmp;
	scanf("%s",ch);
	for(int v=1;v<=n;v++) 
		G[u][v]=ch[v-1]-'0'; 
}

void flyod()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&G[i][k]&&G[k][j]) 
					G[i][j]=1;
}

void bfs(int s)
{
	int u,v;
	vis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		for(v=1;v<=n;v++) if(G[u][v])
		{
			if(!vis[v]) q.push(v),vis[v]=1;
			to[v]++;
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) read(i);
	flyod();
	for(int i=1;i<=n;i++)
		if(!vis[i]) bfs(i);
	int ans=n;
	for(int i=1;i<=n;i++)
		ans+=to[i];
	printf("%d",ans);
	return 0;
}
