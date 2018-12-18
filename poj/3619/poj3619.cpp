#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=1010;
int n,k,s,t,r,rea,rest;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
	  {
	  	scanf("%d%d%d",&s,&t,&r);
	  	rea=n/s;
	  	if(n%s) rea++;
	  	if(n%(s*t)==0) rest=(n/(s*t)-1)*r;
	  	//若刚好读完，则可以少一次休息时间 
	  	else rest=n/(s*t)*r;
	  	printf("%d\n",rea+rest);
	  }
	return 0;
}