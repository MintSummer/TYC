#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
int n,s,a[20005],ans=0,i,j;

bool cmp(int p,int q)
{
	return p<q;
}

int main()
{
	scanf("%d%d",&n,&s);
	for(i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	for(i=1;i<=n;i++) 
	  {
	  	for(j=i+1;j<=n;j++)
	  	  {
	  	  	if(a[i]+a[j]>s) break;
	  	  }
	  	ans+=(j-i-1);
	  }
	printf("%d",ans);
	return 0;
}