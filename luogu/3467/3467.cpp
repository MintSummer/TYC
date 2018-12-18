#include<bits/stdc++.h>
using namespace std;
const int MAXN=250010;
typedef long long LL;
LL n,ans;
LL h[MAXN],w[MAXN],st[MAXN],top=0;

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&w[i],&h[i]);
	ans=n;
	for(int i=1;i<=n;i++)
	{
		while(top>=1&&st[top]>h[i]) top--;
		while(st[top]==h[i]) ans--,top--;
		st[++top]=h[i];
	}
	printf("%lld",ans);
	return 0;
}
