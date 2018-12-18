#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
	const int N=210;
    int n,a[N];
    ll dp[N][N];

    ll dfs(int l,int r)
    {
        ll &ans=dp[l][r];
        if(ans) return ans;
		if(l==r) return ans=0;
        if(l+1==r) return ans=a[l]*a[r]*a[r+1];
        for(int i=l;i<r;i++)
            ans=max(ans,dfs(l,i)+dfs(i+1,r)+(ll)a[l]*a[i+1]*a[r+1]);
        return ans;
    }

    void work()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]),a[n+i]=a[i];
		a[(n<<1)+1]=a[1];
        ll ans=0;
		for(int s=1;s<=n;s++)//枚举环的断点
			ans=max(ans,dfs(s,s+n-1));
		printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
