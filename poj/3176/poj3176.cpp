#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int n;
int a[400][400];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  {
	  	for(int j=1;j<=i;j++)
	  	  scanf("%d",&a[i][j]);
	  }
	for(int i=n-1;i>=1;i--)
	  {
	  	for(int j=1;j<=i;j++)
	  	  {
	  	  	if(a[i+1][j]>a[i+1][j+1])
	  	  	  a[i][j]+=a[i+1][j];
	  	  	else a[i][j]+=a[i+1][j+1];
	  	  }
	  }
	printf("%d",a[1][1]);
	return 0;
}