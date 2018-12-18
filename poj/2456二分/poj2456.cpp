#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

const int MAXN=100010;
long long n,c,l,mid,ans,r,e=0,f=0x3f3f3f3f,sum,cow;
long long x[MAXN];

long long MIN(long long a,long long b)
{
	if(a<b) return a;
	else return b;
}

long long MAX(long long a,long long b)
{
	if(a>b) return a;
	else return b;
}

bool cmp(long long a,long long b)
{
	return a<b;
}

bool check(long long a)
{
	sum=0,cow=1;
	for(int i=2;i<=n;i++)
	  {
	  	sum+=x[i]-x[i-1];
	  	if(sum>=a) 
	  	  {
	  	  	cow++;
	  	  	sum=0;
	  	  }
	  }
	if(cow>=c) return true;
	else return false;
}

int main()
{
	scanf("%lld%lld",&n,&c);
	for(int i=1;i<=n;i++)
	  scanf("%lld",&x[i]),f=MIN(f,x[i]),e=MAX(e,x[i]);
	sort(x+1,x+1+n,cmp);
	l=0,r=e-f;
	while(l<=r)
	  {
	  	mid=(l+r)>>1;
	  	if(check(mid)) l=mid+1,ans=mid;
	  	else r=mid-1;
	  }
	printf("%lld",ans);
	return 0;
}