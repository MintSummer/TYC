//tyc
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long n,l,sum[50010];
long long dp[50010],q[50010];

inline double y(long long a)
{
	return dp[a]+sum[a]*sum[a];
}

inline double x(long long a)
{
	return sum[a];
}

inline double g(long long a,long long b)
{
	if(x(b)-x(a)==0) return 0x3f3f3f3f;
	else return (y(b)-y(a))/(x(b)-x(a));
}

int main()
{
	scanf("%lld%lld",&n,&l);
	long long a;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a);
		sum[i]=sum[i-1]+a+1;
	}
	
	int h=0,t=1;
	q[0]=0;
	for(int i=1;i<=n;i++)	
	{
		while( h+1<t && g(q[h],q[h+1]) <= 2*(sum[i]-1-l) )
			h++;
		dp[i]=dp[q[h]]+(sum[i]-sum[q[h]]-l-1)*(sum[i]-sum[q[h]]-l-1);
		while( h+1<t && g(i,q[t-1]) <= g(q[t-1],q[t-2]) )
			t--;
		q[t++]=i;
	}

	printf("%lld",dp[n]);
	return 0;
}
