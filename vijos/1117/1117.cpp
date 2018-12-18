#include<bits/stdc++.h>
using namespace std;
int n,k,dp[210][10];

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<=n;i++) dp[i][1]=1; 
    for(int i=2;i<=n;i++)
	for(int j=2;j<=min(k,i);j++)
	    dp[i][j]=dp[i-1][j-1]+dp[i-j][j];
    printf("%d",dp[n][k]);
    return 0;
}
