#include<bits/stdc++.h>
using namespace std;
int dp[5010][5010];

int main()
{
    int n,r,ans=0;
    scanf("%d%d",&n,&r);
    int x,y,v;
    for(int i=0;i<n;i++)
    {
	scanf("%d%d%d",&x,&y,&v);
	dp[x+1][y+1]=v;
    }
    for(int i=1;i<=5001;i++)
        for(int j=1;j<=5001;j++)
	    dp[i][j]=dp[i-1][j]+dp[i][j-1]+dp[i][j]-dp[i-1][j-1];
    for(int i=r;i<=5001;i++)
	for(int j=r;j<=5001;j++)
  	    ans=max(ans,dp[i][j]-dp[i-r][j]-dp[i][j-r]+dp[i-r][j-r]);
    printf("%d",ans);
    return 0;
}
