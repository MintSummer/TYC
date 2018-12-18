#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=5010;
int n,m,k;
ll a[MAXN],ans,dp[MAXN][MAXN],sum[MAXN];

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) 
	scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
    for(int i=m;i<=n;i++)
    {
	ll tmp=sum[i]-sum[i-m];
	for(int j=1;j<=k;j++)//是否选取i-m+1到i这段
	    dp[i][j]=max(dp[i-1][j],dp[i-m][j-1]+tmp);
	ans=max(ans,dp[i][k]);
    }
    printf("%lld",ans);
    return 0;
}
