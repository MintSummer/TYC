#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int g[1005][1005],count=0;
int dx[9]={0,-1,-1,0,1,1,1,0,-1};
int dy[9]={0,0,1,1,1,0,-1,-1,-1};

void dfs(int x,int y)
{
	for(int i=1;i<=8;i++)
	  if(g[x+dx[i]][y+dy[i]]) 
	    g[x+dx[i]][y+dy[i]]=0,dfs(x+dx[i],y+dy[i]);
	return;
}

int main()
{
	int N,M;
	char ch;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
	  for(int j=1;j<=M;j++)
	    {
		    cin>>ch;
	    	if(ch=='W') g[i][j]=1;
	    	else g[i][j]=0;
	    }
	for(int i=1;i<=N;i++)
	  for(int j=1;j<=M;j++)
	    if(g[i][j]==1) count++,g[i][j]=0,dfs(i,j);
	printf("%d",count);
	return 0;
}