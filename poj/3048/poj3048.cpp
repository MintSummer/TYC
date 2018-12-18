#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
using namespace std;
int n;

int search(int x)
{
	int end=0;
	for(int i=1;i<=x;i++)
	  {
	  	if(x%i==0) 
	  	  {
	  	  	end=i;
	  	  	x/=i;
	  	  }
	  }
	return end;
}

int main()
{
	cin>>n;
	int a;
	int ans=0,mx=0,f;
	for(int i=1;i<=n;i++)
	  {
	  	cin>>a;
	  	ans=search(a);
	  	if(ans>mx) 
	  	  {
	  	  	f=a;
	  	  	mx=ans;
	  	  }
	  }
	printf("%d",f);
}