#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,l,c[50010],sum[50010];
int dp[5010][5010];//存不了这么大的 

int main()
{
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++)
	  scanf("%d",&c[i]),sum[i]+=c[i];
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
	  {
	  	for(int j=1;j<=i;j++)
	  	  dp[i][j]=dp[i-j][1]+sum[i]-sum[j]+l*(i-j-1);
	  }
	int mn=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
	  if(mn>dp[n][i]) mn=dp[n][i];
	 printf("%d",mn);
	 return 0; 
}
