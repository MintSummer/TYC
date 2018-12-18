#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=125;
int n,k[MAXN],c[MAXN];
ll m,dp[MAXN][MAXN*2000+10];
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>k[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    dp[0][0]=1;
    ll mx=0;
    for(int i=1;i<=n;i++)
    {
		for(int j=0;j<=mx;j++) dp[i][j]=dp[i-1][j];
		for(int j=2;j<=k[i];j++)
			for(int k=j*c[i];k<=j*c[i]+mx;k++)
				dp[i][k]=min(m,max(dp[i][k],dp[i-1][k-j*c[i]]*j));
		mx+=c[i]*k[i];
    }
    for(int i=0;i<=mx;i++)
		if(dp[n][i]==m) {cout<<i;break;}
    return 0;
}
