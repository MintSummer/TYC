#include<bits/stdc++.h>
using namespace std;
int v,m[30],n;
long long dp[10010];

int main()
{
	cin>>v>>n;
	for(int i=1;i<=v;i++) cin>>m[i];
	dp[0]=1;
	for(int i=1;i<=v;i++)
	  for(int j=m[i];j<=n;j++)
	    dp[j]+=dp[j-m[i]];
	cout<<dp[n];
	return 0;
}
