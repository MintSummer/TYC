#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2000010;
ll n,p,ans=1,cnt=0;
int prime[MAXN],tim[MAXN],vis[MAXN],id[MAXN];
//用id[x]数组记录x的最小质因数是prime数组的第几位

void getpri()
{
	for(int i=2;i<=2*n;i++)
	{
		if(!vis[i]) prime[++cnt]=i,id[i]=cnt;
		for(int j=1;j<=cnt&&i*prime[j]<=2*n;j++)
		{
			vis[i*prime[j]]=1;
			id[i*prime[j]]=j;
			if(i%prime[j]==0) break;
		}
	}
}

void add(int x,int t)
{
	while(x!=1)
	{
		tim[id[x]]+=t;
		x/=prime[id[x]];
	}
}

int main()
{
	scanf("%lld%lld",&n,&p);
	getpri();
	for(int i=n+1;i<=2*n;i++) add(i,1);
	for(int i=1;i<=n;i++) add(i,-1);
	add(n+1,-1);
	for(int i=1;i<=cnt;i++)
		while(tim[i]--) ans=(ans*prime[i])%p;
	printf("%lld",ans);
	return 0;
}
