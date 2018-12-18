#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
int d[100005];
long long n,s=0;

int main()
{
	scanf("%lld",&n);
	for(int i=0;;i++)
	  {
	     d[i]=n%(-2);
	     n=n/(-2);
		 if(d[i]<0) d[i]=d[i]-(-2),n++;
		 s++;
		 if(n==0) break;	
	  }
	for(int j=s-1;j>=0;j--) printf("%d",d[j]);
	return 0;
}