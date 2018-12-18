#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
long long n,x[10010],sum=0;
long long sl,sr;
bool cmp(long long a,long long b)
{
	return a<b;
}

int main()
{
	sl=sr=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	  {
	  	scanf("%lld",&x[i]);
	  	sr+=x[i];
	  }
	sort(x+1,x+1+n,cmp);
	for(int i=1;i<=n;i++)
	  {
	    sr-=x[i];
	    sum+=sr-x[i]*(n-i);
	    sum+=x[i]*(i-1)-sl;
	  	sl+=x[i];
	  }
	printf("%lld",sum);
	return 0;
}