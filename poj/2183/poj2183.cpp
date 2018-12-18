#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
int tim[1000005];
bool vis[1000005];
long long n;

int main()
{
	int t=0,mt; 
	memset(vis,0,sizeof(vis));
	memset(tim,0,sizeof(tim));
	scanf("%lld",&n);
	while(true)
	  {
	  	t++;
	  	n=n/10;
	  	n=n%10000;
	  	n=(n*n)%1000000;
	  	if(vis[n]==0)
	  	  {
	  	  	vis[n]=1;
	  	  	tim[n]=t;
	  	  }
	  	else
	  	  {
	  	  	cout<<n<<' '<<t-tim[n]<<' '<<t;
	  	  	break;
	  	  }
	  } 
	return 0;
} 