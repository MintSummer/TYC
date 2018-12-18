#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[15];
ll dp[15][2][2][2][15][15][2],t,ch1,ch2;

void change(ll x)
{
	t=0;
	while(x)
		a[++t]=x%10,x/=10;
}

ll dfs(int len,int cur,int f4,int f8,int last,int tim,int flag)
{
	if(dp[len][cur][f4][f8][last][tim][flag]!=-1) return dp[len][cur][f4][f8][last][tim][flag];
	if(f4&&f8) return dp[len][cur][f4][f8][last][tim][flag]=0;
	if(len==0) return dp[len][cur][f4][f8][last][tim][flag]=flag;
	ll res=0;
	for(int i=0;i<10;i++)
	{
		if(len==t&&i==0) continue;
		if(cur&&a[len]<i) break;
		int ncur=0,nf4,nf8,nflag=0,ntim=1;
		ncur=(cur&&(i==a[len]));
		nf4=(f4||(i==4)),nf8=(f8||(i==8));
		if(i==last) ntim=tim+1;
		if(ntim>=3||flag) nflag=1;
		res+=dfs(len-1,ncur,nf4,nf8,i,ntim,nflag);
	}
	return dp[len][cur][f4][f8][last][tim][flag]=res;
}

int main()
{
	scanf("%lld%lld",&ch1,&ch2);
	change(ch2);
	memset(dp,-1,sizeof(dp));
	ll ans=dfs(t,1,0,0,0,0,0);
	change(ch1-1);
	if(ch1!=10000000000) change(ch1-1);
    else ans++,change(ch1);
	memset(dp,-1,sizeof(dp));
	ans-=dfs(t,1,0,0,0,0,0);
	printf("%lld",ans);
	return 0;
}
