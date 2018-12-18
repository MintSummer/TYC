#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int n,con,ans=0;

void dfs(int a)
{
	for(int i=a;i<=con;i++)
	  {
	  	if(i==con) 
		  {
		  	ans++;
		  	return;
		  } 
		con-=i;
	  }
}

int main()
{
    cin>>n;
	for(int i=1;i<=n;i++)
	  {
	    con=n;
	  	dfs(i);
	  }	
    printf("%d",ans);
    return 0;
}