#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int n,t,p,r,s[1010],b;

int main()
{
	scanf("%d%d",&n,&t);
	int mx;
	for(int i=1;i<=n;i++)
	  scanf("%d",&s[i]);
	if(n==1)
	  for(int i=1;i<=t;i++)
	  	printf("1\n");
	else
	  {
	  	while(t)
	  	  {
	  	  	mx=1;
	  	  	for(int i=2;i<=n;i++)
	          if(s[mx]<s[i]) mx=i;
	  	  	printf("%d\n",mx);
	  	  	b=mx;
	  	  	t--;
	  	  	p=s[mx]/(n-1);
	  	  	r=s[mx]%(n-1);
	  	  	s[mx]=0;
	  	  	if(r==0)
	  	  	  {
	  	  	  	for(int i=1;i<=n;i++)
	  	  	  	  if(i!=b) s[i]+=p;
	  	  	  }
	  	  	else
	  	  	  {
	  	  	  	for(int i=1;i<=n;i++)
	  	  	  	  if(i!=b) s[i]+=p;
	  	  	  	for(int i=1;i<=r;i++)
	  	  	  	  {
	  	  	  	  	if(i!=b) s[i]++;
	  	  	  	  	else r++;
	  	  	  	  }
	  	  	  }
	  	  }
	  }
	return 0;
}