#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int n;
int vis[1000010];
int main(void)
{
	cin>>n;
	memset(vis,-1,sizeof(vis));
	vis[n]=0;
	for(int i=1;;i++)
	{
		n=pow(n%100000/10,2);
		if(n>=1000000)n=n%1000000;
		if(vis[n]==-1)vis[n]=i;
		else
		{
			printf("%d %d %d",n,i-vis[n],i);
			return 0;
		}
	}
} 
