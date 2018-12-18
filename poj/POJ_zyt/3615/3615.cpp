#include<cstdio>
#include<climits>
#include<algorithm>
#include<cctype>
#include<cstdlib>
#include<iostream>
using namespace std; 
int n,m,t;
int map[310][310];
int read()
{
	int ans=0;
	char a[2];
	a[0]=getchar();
	a[1]='\0';
	while(!isdigit(a[0]))a[0]=getchar();
	while(isdigit(a[0]))ans=ans*10+atoi(a),a[0]=getchar();
	return ans;
}
int main(void)
{
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			map[i][j]=(i==j?0:INT_MAX/2);
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		a=read();
		b=read();
		c=read();
		map[a][b]=c;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				map[i][j]=min(map[i][j],max(map[i][k],map[k][j]));
	while(t--)
	{
		int a,b;
		a=read();
		b=read();
		if(map[a][b]==INT_MAX/2)printf("-1\n");
		else printf("%d\n",map[a][b]);
	}
	return 0;
}
