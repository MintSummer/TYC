#include<bits/stdc++.h>
using namespace std;
int t,m,w[110],c[110],dp[1100],ans;

int main()
{
    scanf("%d%d",&t,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&c[i],&w[i]);
    for(int i=1;i<=m;i++)
	for(int j=t;j>=c[i];j--)
	    dp[j]=max(dp[j],dp[j-c[i]]+w[i]);
    for(int i=0;i<=t;i++)ans=max(ans,dp[i]);
    printf("%d",ans);
    return 0;
}
