#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[360][360],dp[360][360];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	    scanf("%d",&a[i][j]);
    for(int i=n;i>=1;i--)
	for(int j=1;j<=i;j++)
	    dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+a[i][j];
    printf("%d",dp[1][1]);
    return 0;
}