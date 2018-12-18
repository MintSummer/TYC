#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int n,m,cnt;
vector<int>g[1010];
int sum[1010],vis[1010],vis2[1010];
void dfs(int s)
{
	cnt++;
	vis[s]=true;
	for(int i=0;i<g[s].size();i++)
	{
		int v=g[s][i];
		if(!vis[v])
			dfs(v);
	}
}
int main(void)
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int a,b;
		cin>>a>>b;
		g[a].push_back(b);
	}
	memset(vis,-1,sizeof(vis));
	int ans=0;
	for(int k=1;k<=n;k++)
	{
		memset(vis,0,sizeof(vis));
		dfs(k);
		cnt--;
	}
	cout<<n*(n-1)/2-cnt;
	return 0;
} 
