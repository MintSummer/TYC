#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
	const int N=40;
    int n,val[N],root[N][N];
    ll dp[N][N];

    ll dfs(int l,int r)
    {
        ll &ans=dp[l][r];
		if(ans) return ans;
        if(l>r) return ans=1;
		if(l==r) 
		{
			root[l][r]=l;
			return ans=val[l];
		}
        for(int rt=l;rt<=r;rt++)
        {
            ll tmp=val[rt]+(ll)dfs(l,rt-1)*dfs(rt+1,r);
            if(tmp>ans) 
                ans=tmp,root[l][r]=rt;
        }
        return ans;
    }

	void print(int l,int r)
	{
		if(l>r) return;
		printf("%d ",root[l][r]);
		if(l==r) return;
		print(l,root[l][r]-1);
		print(root[l][r]+1,r);
	}

    void work()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&val[i]);
        ll ans=dfs(1,n);
        printf("%lld\n",ans);	
		print(1,n);	
    }
}

int main()
{
    TYC::work();
    return 0;
}
