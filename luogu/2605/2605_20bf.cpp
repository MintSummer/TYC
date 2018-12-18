#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll INF=(1LL<<60);
    const int N=1010;
    int n,num,L[N],R[N];
    ll dis[N],c[N],r[N],w[N],sum[N],dp[N][110];
    
    ll cal(int l,int r)
    {
        ll sum=0;
        for(int i=l+1;i<r;i++)
            if(L[i]>l&&R[i]<r) sum+=w[i];
        return sum;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n>>num;
        for(int i=2;i<=n;i++) cin>>dis[i];
        for(int i=1;i<=n;i++) cin>>c[i];
        for(int i=1;i<=n;i++) cin>>r[i];
        for(int i=1;i<=n;i++) 
            cin>>w[i],sum[i]=sum[i-1]+w[i];
        for(int i=1;i<=n;i++)   
            for(int j=1;j<=num;j++)
                dp[i][j]=INF;
        for(int i=1;i<=n;i++)
        {
            L[i]=lower_bound(dis+1,dis+1+n,dis[i]-r[i])-dis;
            R[i]=upper_bound(dis+1,dis+1+n,dis[i]+r[i])-dis-1;
        }
        dp[0][0]=0;
        ll ans=INF;
        for(int i=1;i<=n;i++)
        {
            ll sum=0,res=0;
            for(int j=i+1;j<=n;j++)
                if(L[j]>i) res+=w[j];
			dp[i][1]=cal(0,i)+c[i];
			ans=min(ans,dp[i][1]+res);
            for(int j=2;j<=num;j++)
            {
                for(int k=j-1;k<i;k++)
                    dp[i][j]=min(dp[i][j],dp[k][j-1]+cal(k,i)+c[i]);
                ans=min(ans,dp[i][j]+res);
            }
        }
        cout<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}
