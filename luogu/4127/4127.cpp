#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	ll dp[20][2][170][170];
	int mod,a[20];

	inline int Mod(int x)
	{
		return x>=mod?x%mod:x;
	}

	ll calc(string &str)
	{
		ll now=0,num=0;
		for(int i=0,sz=str.size();i<sz;i++)
			num+=str[i]-'0',now=now*10+str[i]-'0';
		return now%num==0;
	}

	ll dfs(int len,int cur,int sum,int res)
	{
		ll &ans=dp[len][cur][sum][res];
		if(~ans) return ans;
		if(!len) return ans=(res==0&&sum==mod);
		ans=0;
		for(int i=0;i<10;i++)
		{
			if(cur&&i>a[len]) break;
			ans+=dfs(len-1,cur&(i==a[len]),sum+i,Mod(res*10+i));
		}
		return ans;
	}

	ll solve(string &str)
	{
		int len=str.size();
		for(int i=0;i<len;i++) a[len-i]=str[i]-'0';
		ll ans=0;
		for(mod=1;mod<=len*9;mod++)	
		{
			memset(dp,-1,sizeof(dp));
			ans+=dfs(len,1,0,0);
		}
		return ans;
	}

	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		string A,B;
		cin>>A>>B;
		cout<<solve(B)-solve(A)+calc(A)<<"\n";
	}
}

int main()
{
	TYC::work();
	return 0;
}
