#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1010;
    const ll inf=(1LL<<61);
    ll n,a[N],b[N],dp[N][N],ans[N];

    ll gcd(ll a,ll b)
	{ 
		return !b?a:gcd(b,a%b); 
	}

    void work()
	{
        scanf("%lld",&n);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
        for(int i=1;i<=n;i++) 
			for(int j=1;j<=n;j++) 
				dp[i][j]=-inf;
        for(int i=1;i<n;i++) 
			if(gcd(a[i],a[i+1])!=1) 
				dp[i][i+1]=b[i]+b[i+1];
        for(int len=4;len<=n;len+=2)
            for(int l=1,r=l+len-1;r<=n;l++,r++)
            {
                if(gcd(a[l],a[r])!=1)
                    dp[l][r]=max(dp[l][r],dp[l+1][r-1]+b[l]+b[r]);
                for(int k=l+1;k<r;k++)
                    dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);		
            }
        for(int i=2;i<=n;i++)
		{
            ans[i]=ans[i-1];
            for(int j=1;j<=i;j++)
                ans[i]=max(ans[i],ans[j-1]+dp[j][i]);
        }
        printf("%lld",ans[n]);
        return ;
    }
}	

int main()
{
    TYC::work();
    return 0;
}
