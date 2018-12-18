#include<iostream>
#include<algorithm>
using namespace std;
bool map[110][110];
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
int n,m,k,tmp,ans;
void dfs(int x,int y)
{
	map[x][y]=false;
	tmp++;
	for(int i=0;i<4;i++)
			if(map[x+dx[i]][y+dy[i]])dfs(x+dx[i],y+dy[i]);
}
int main(void)
{
	cin>>n>>m>>k;
	for(int i=0;i<k;i++)
	{
		int a,b;
		cin>>a>>b;
		map[a][b]=true;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j])
			{
				tmp=0;
				dfs(i,j);
				ans=max(ans,tmp);
			}
	cout<<ans;
	return 0;
}
