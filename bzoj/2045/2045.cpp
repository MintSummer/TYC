//¿ªlong long °¡! 
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=1e6+10;
int a,b,d;
int cnt=0,prime[MAXN],miu[MAXN],vis[MAXN];

void mobi()
{
	miu[1]=1;
	for(int i=2;i<=MAXN;i++)
	{
		if(!vis[i]) prime[++cnt]=i,miu[i]=-1;
		for(int j=1;j<=cnt&&i*prime[j]<=MAXN;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) {miu[i*prime[j]]=0;break;}
			miu[i*prime[j]]=-miu[i];
		}
	}
}

inline LL F(int k)
{
	return (LL)(a/k)*(b/k);
}

int main()
{
	mobi();
	scanf("%d%d%d",&a,&b,&d);
	if(d==0) {printf("0");return 0;} 
	a/=d,b/=d;
	if(a>b) swap(a,b);
	long long ans=0;
	for(int k=1;k<=a;k++) ans+=miu[k]*F(k);
	printf("%lld",ans);
	return 0;
}
