#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=3010;

	int tot,n;
	ll L,R,ans,arr[N],lucky[N];

	inline void get_num(ll now)
	{
		if(now) arr[++tot]=now;
		if(now*10+6<=R) get_num(now*10+6);
	   	if(now*10+8<=R) get_num(now*10+8);	
	}

	bool cmp(const ll &x,const ll &y)
	{
		return x>y;
	}

	ll gcd(ll a,ll b)
	{
		return !b?a:gcd(b,a%b);
	}

	inline ll calc(ll x)
	{
		return R/x-L/x+(L%x==0);
	}

	void dfs(int now,int num,ll lcm)
	{
		if(lcm>R) return;
		if(lcm!=1) ans+=num&1?calc(lcm):-calc(lcm);
		for(int i=now;i<=n;i++)
		{
			ll t=lcm/gcd(lcm,lucky[i]);
			if((double)t*lucky[i]<=R)
				dfs(i+1,num+1,t*lucky[i]);
		}
	}

	void work()
	{
		scanf("%lld%lld",&L,&R);
		get_num(0);
		for(int i=1;i<=tot;i++)
		{
			int flag=0;
			for(int j=1;j<i;j++)
				if(arr[i]%arr[j]==0) flag=1;
			if(flag) continue;
			lucky[++n]=arr[i];
		}
		sort(lucky+1,lucky+1+n,cmp);
		dfs(1,0,1);
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
