#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	typedef long long ll;
	ll dp[15][3][3][12];
	int n,x[15];
	
	ll dfs(int len,int cur,int zero,int last)
	{
		if(dp[len][cur][zero][last]) return dp[len][cur][zero][last];
		if(!len) return dp[len][cur][zero][last]=1;
		ll tmp=0;
		for(int i=0;i<10;i++)
		{
			if(cur&&i>x[len]) break;
			if(len!=n&&!zero&&abs(i-last)<=1) continue;
			tmp+=dfs(len-1,cur&&(i==x[len]),zero&&(i==0),i);
		}
		return dp[len][cur][zero][last]=tmp;
	}
	
	ll solve(ll now)
	{
		memset(dp,0,sizeof(dp));
		n=0;
		while(now)
		{
			x[++n]=now%10;
			now/=10;
		}
		return dfs(n,1,1,0);
	}
	
	void work()
	{
		ios::sync_with_stdio(false);
		ll A,B;
		cin>>A>>B;
		printf("%lld",solve(B)-solve(A-1));
	}
}

int main()
{
	TYC::work();
	return 0;
} 
