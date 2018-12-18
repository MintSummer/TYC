//TYC

#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n;
int dp[5][5][5][5][5];

int getin(char c)
{
	if(c=='M') return 1;
	if(c=='F') return 2;
	return 3;
}

int meikuang(int x,int y,int z)
{
	int tot=1;
	if(x!=0&&x!=y&&x!=z) tot++;
	if(y!=0&&y!=z) tot++;
	return tot;
}

int main()
{
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	char ch[100010];
	scanf("%s",&ch);
	int now,before,add,food;
	dp[0][0][0][0][0]=0;
	for(int i=0;i<n;i++)
	  for(int x1=0;x1<=3;x1++)
	    for(int x2=0;x2<=3;x2++)
	      for(int y1=0;y1<=3;y1++)
	        for(int y2=0;y2<=3;y2++)
	          {
	          	food=getin(ch[i]);
	          	before=i%4,now=(i+1)%4;
	          	if(dp[before][x1][x2][y1][y2]==-1) continue;
	          	add=meikuang(x1,x2,food);
	          	dp[now][x2][food][y1][y2]=max(dp[now][x2][food][y1][y2],dp[before][x1][x2][y1][y2]+add);
	          	add=meikuang(y1,y2,food);
	          	dp[now][x1][x2][y2][food]=max(dp[now][x1][x2][y2][food],dp[before][x1][x2][y1][y2]+add);
	          }
	int mx=0;
	n=n%4;
	for(int x1=1;x1<=3;x1++)
	    for(int x2=1;x2<=3;x2++)
	      for(int y1=1;y1<=3;y1++)
	        for(int y2=1;y2<=3;y2++)
	          if(dp[n][x1][x2][y1][y2]>mx) mx=dp[n][x1][x2][y1][y2];
	printf("%d",mx);
	return 0;
} 
