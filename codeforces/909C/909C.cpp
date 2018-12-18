#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const ll p=1e9+7;
	const int N=5010;
	int n,a[N];
	ll dp[N][N];
	
	void work()
	{
		ios::sync_with_stdio(false);
		cin>>n;
		string str;
		for(int i=1;i<=n;i++) 
		{
			cin>>str;
			a[i]=(str[0]=='f');
		}
		dp[1][1]=1;
		for(int i=2;i<=n;i++)
		{
			if(a[i-1]) 
				for(int j=1;j<=i;j++) 
					dp[i][j]=dp[i-1][j-1];
			else 
				for(int j=i;j;j--) 
					dp[i][j]=(dp[i][j+1]+dp[i-1][j])%p;
		}
		ll ans=0;
		for(int i=1;i<=n;i++) ans=(ans+dp[n][i])%p;
		cout<<ans;
	}
}

int main()
{
	TYC::work();
	return 0;
}
