#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int n,S;
int a[25][25],cnt;
int main()
{
	scanf("%d%d",&n,&S);
	cnt=S;
	for(int i=1;i<=n;i++)
	  {
	  	for(int j=1;j<=i;j++)
	  	  {
	  	  	a[j][i]=cnt;
			cnt++;
			if(cnt==10) cnt=1;
	  	  }
	  }
	for(int i=1;i<=n;i++)
	  {
	  	if(i!=1)
	  	  {
	  	  	for(int k=1;k<=i-1;k++)
	  	  	  {
	  	  	  	printf("  ");
	  	  	  }
	  	  }
	  	for(int j=i;j<=n;j++)
	      {
	    	cout<<a[i][j]<<' ';
	      }
	    cout<<endl;
	  }
	return 0;
}