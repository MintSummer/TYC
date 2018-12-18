#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
long long n,s,ans=0,mn;
long long c[10010],y[10010];

long long MIN(long long a,long long b)
{
	return a<b?a:b;
}

int main()
{
	cin>>n>>s;
	for(int i=1;i<=n;i++)
	  cin>>c[i]>>y[i];
	ans=c[1]*y[1];
	mn=c[1];
	for(int i=2;i<=n;i++)
	  {
	  	mn=MIN(mn+s,c[i]);
	  	ans+=mn*y[i];
	  }
	cout<<ans;
	return 0;
}