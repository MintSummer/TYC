#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int vis[10010][510],d[10010],m,n;
const int INF=10000000;
int dp(int i,int j)
{
	if(i>n)return -INF;
	if(vis[i][j]!=-1)return vis[i][j];
	if(n-i<j)return -INF;
	if(i==n||n-i==j)return 0;
	if(j==m)return vis[i][j]=dp(i+j,0);
	if(j==0)return vis[i][j]=max(dp(i+1,0),dp(i+1,j+1)+d[i]);
	else return vis[i][j]=max(dp(i+j,0),dp(i+1,j+1)+d[i]);
}
int main(void)
{
	memset(vis,-1,sizeof(vis));
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",&d[i]);
	printf("%d",dp(0,0));
	return 0;
}
