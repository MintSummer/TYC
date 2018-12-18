#include<iostream>
#include<cstdlib>
using namespace std;
bool vis[10];
const int yanghui[11][11]
{
	{0},{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1},{1,5,10,10,5,1},{1,6,15,20,15,6,1},
	{1,7,21,35,35,21,7,1},{1,8,28,56,70,56,28,8,1},{1,9,36,84,126,126,84,36,9,1}
};
int n,s,a[11];
void dfs(int cnt)
{
	if(cnt==n)
	{
		int ans=0; 
		for(int i=0;i<n;i++)
			ans+=yanghui[n][i]*a[i];
		if(ans==s)
		{
			for(int i=0;i<n;i++)cout<<a[i]<<" ";
			exit(0);
		}
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			if(!vis[i])
			{
				vis[i]=true;
				a[cnt]=i;
				dfs(cnt+1);
				vis[i]=false;
			}
		}
	}
}
int main(void)
{
	cin>>n>>s;
	dfs(0);
	return 0;
} 
