#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
vector<int> list[1010],cow;
int k,n,m,ans,done[1010];
bool vis[1010];
int main(void)
{
	cin>>k>>n>>m;
	for(int i=0;i<k;i++)
	{
		int a;
		cin>>a;
		cow.push_back(a);
	}
	for(int i=0;i<m;i++)
	{
		int a,b;
		cin>>a>>b;
		list[a].push_back(b);
	}
	for(int i=0;i<k;i++)
	{
		memset(vis,0,sizeof(vis));
		queue <int> q;
		q.push(cow[i]);
		vis[cow[i]]=true;
		done[cow[i]]++;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int j=0;j<list[u].size();j++)
			{
				int v=list[u][j];
				if(!vis[v])
				{
					done[v]++;
					q.push(v);
					vis[v]=true;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(done[i]==k)ans++;
	cout<<ans;
	return 0;
} 
