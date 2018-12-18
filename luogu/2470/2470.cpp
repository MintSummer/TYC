#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    typedef pair<ll,ll> pa;
    const int N=60,inf=0x3f3f3f3f;
    const ll seed=233,p1=1e9+7,p2=1e9+9;
    int n,dp[N][N][2];
    char str[N];
    ll Pow1[N],Pow2[N],Sum1[N],Sum2[N];
    
    inline void init()
    {
        Pow1[0]=Pow2[0]=1;
        for(int i=1;i<=n;i++)
        {
            Pow1[i]=Pow1[i-1]*seed%p1;
            Pow2[i]=Pow2[i-1]*seed%p2;
            Sum1[i]=(Sum1[i-1]*seed%p1+str[i]-'a')%p1;
            Sum2[i]=(Sum2[i-1]*seed%p2+str[i]-'a')%p2;
        }
    }

    inline pa hash(int l,int r)
    {
        ll ans1=(Sum1[r]-Sum1[l-1]*Pow1[r-l+1]%p1+p1)%p1;
        ll ans2=(Sum2[r]-Sum2[l-1]*Pow2[r-l+1]%p2+p2)%p2;
        return make_pair(ans1,ans2);
    }

    inline int Min(int &x,int y)
    {
        return x=(x<y?x:y);
    }

    void dfs(int l,int r)
    {
        if(dp[l][r][0] != inf || dp[l][r][1] != inf) return;
        if(l==r) {dp[l][r][0]=2;return;}
        int mid=(l+r)>>1;
        for(int i=l;i<r;i++)
        {
            dfs(l,i),dfs(i+1,r);
            Min(dp[l][r][1],min(dp[l][i][0],dp[l][i][1])+min(dp[i+1][r][0],dp[i+1][r][1]));
            Min(dp[l][r][0],dp[l][i][0]+r-i);
        }
        if((l&1)!=(r&1)&&hash(l,mid)==hash(mid+1,r))
            Min(dp[l][r][0],dp[l][mid][0]+1);
    }

    void work()
    {
        scanf("%s",str+1);
        n=strlen(str+1);
        init();
        memset(dp,inf,sizeof(dp));
        dfs(1,n);
        printf("%d\n",min(dp[1][n][0],dp[1][n][1])-1);
    }
}

int main()
{
    TYC::work();
    return 0;
}