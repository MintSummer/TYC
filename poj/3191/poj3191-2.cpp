#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
long long n;
int d[100005];

int main()
{
	cin>>n;
	int s=0;
	for(int i=0;;i++)
	  {
	  	d[i]=n%(-2);
	  	n=n/(-2);
	  	if(d[s]<0)
	  	  d[i]=d[i]-(-2),n++;
	  	s++;
	  	if(n==0) break;
	  }
	for(int i=s-1;i>=0;i--)
	  printf("%d",d[i]);
	return 0;
}