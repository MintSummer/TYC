#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=4e4+10;
    int n,m,val[N],weight[N],num[N],dp[N];
    
    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>val[i]>>weight[i]>>num[i];
        for(int i=1;i<=m;i++) dp[i]=-0x3f3f3f3f;
        for(int i=1;i<=n;i++)
        {
            int tmp=min(num[i],m/weight[i]);
            for(int k=1;tmp>0;k<<=1)
            {
                if(k>tmp) k=tmp;
                tmp-=k;
                for(int j=m;j>=weight[i]*k;j--)
                    dp[j]=max(dp[j],dp[j-weight[i]*k]+val[i]*k);
            }
        }
		int ans=0;
		for(int i=1;i<=m;i++) ans=max(ans,dp[i]);
		cout<<ans<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
} 
