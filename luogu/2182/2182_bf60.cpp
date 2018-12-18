#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const ll p=1000000007;
	const int N=110,MX=(1<<10)+10;
	int n,m,k,bin[110];
	ll dp[MX][N];
	vector<int> G[MX];

	inline void Mod(ll &x) {x=(x>=p?x-p:x);}

	int calc(string &str)
	{
		int ans=0;
		for(int i=0;i<n;i++)
			if(str[i]=='1') ans|=bin[i+1];
		return ans;
	}

	bool check(int x,int y)
	{
		int num=0;
		for(int i=1;i<=n;i++)
			if((x&bin[i])!=(y&bin[i])) num++;
		return num==m;
	}

	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		cin>>n>>k>>m;
		string from,to;
		cin>>from>>to;
		bin[1]=1;
		for(int i=2;i<=n;i++) bin[i]=bin[i-1]<<1;
		dp[calc(from)][0]=1;
		for(int i=0;i<(1<<n);i++)
			for(int j=i+1;j<(1<<n);j++)
				if(check(i,j)) 
				{
					G[i].push_back(j);
					G[j].push_back(i);
				}
		for(int i=1;i<=k;i++)
			for(int s=0;s<(1<<n);s++)
				for(int j=0,sz=G[s].size();j<sz;j++)
					Mod(dp[G[s][j]][i]+=dp[s][i-1]);
		cout<<dp[calc(to)][k]<<"\n";
	}
}

int main()
{
	TYC::work();
	return 0;
}
