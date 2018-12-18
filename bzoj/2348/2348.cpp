#include<bits/stdc++.h>
using namespace std;
const double EPS=1e-7;
int n,f[100100];

bool cmp(int a,int b)
{
	return a<b;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&f[i]);
	sort(f+1,f+1+n,cmp);
	long long ans=0;
	for(int h=1,t=1;t<=n;t++)
	{
		while(f[h]+EPS<f[t]*0.9) h++;
		ans+=t-h;
	}
	printf("%lld",ans);
	return 0;
}
