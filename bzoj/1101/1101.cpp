//×ï¶ñµÄlong long 
//from:TYC
#include<bits/stdc++.h>
using namespace std;
const int MAXN=50010;
int T,a,b,d;
int prime[MAXN],mu[MAXN],vis[MAXN],sum[MAXN],cnt=0;

void get_mu()
{
	mu[1]=1;
	for(int i=2;i<=MAXN;i++)
	{
		if(!vis[i]) {prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&i*prime[j]<=MAXN;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) {mu[i*prime[j]]=0;break;}
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=MAXN;i++) sum[i]=sum[i-1]+mu[i];
}

int main()
{
	get_mu();
	scanf("%d",&T);
	while(T--)
	{
		long long ans=0;
		scanf("%d%d%d",&a,&b,&d);
		a/=d,b/=d;
		if(a>b) swap(a,b);
		for(int k=1;k<=a;) 
		{
			int add=min(a/(a/k),b/(b/k));
			ans+=(long long)(sum[add]-sum[k-1])*(a/k)*(b/k);
			k=add+1;
		}
		printf("%lld\n",ans);
	}	
	return 0;
}
