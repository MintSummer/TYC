#include<bits/stdc++.h>
using namespace std;
int h,n,p[110],c[110],dp[60010];

int main()
{
    scanf("%d%d",&n,&h);
    for(int i=1;i<=n;i++) scanf("%d%d",&p[i],&c[i]);
    memset(dp,0x3f3f3f3f,sizeof(dp));
	dp[0]=0;
    for(int i=1;i<=n;i++)
	for(int j=p[i];j<=h+5010;j++)
	    dp[j]=min(dp[j],dp[j-p[i]]+c[i]);
    int mn=0x3f3f3f3f;
    for(int i=h;i<=h+5010;i++) mn=min(mn,dp[i]);
    printf("%d",mn);
    return 0;
}
