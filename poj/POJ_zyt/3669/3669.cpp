#include<iostream>
#include<cstdio> 
#include<queue>
#include<algorithm>
using namespace std;
int m;
const int INF=10000000;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int map[400][400];
bool vis[400][400];
struct note
{
	int x;
	int y;
	int t;
};
queue<note>q;
int main(void)
{
	cin>>m;
	for(int i=0;i<=350;i++)
		for(int j=0;j<=350;j++)
			map[i][j]=INF;
	for(int i=0;i<m;i++)
	{
		int x,y,t;
		scanf("%d%d%d",&x,&y,&t);
		map[x][y]=min(map[x][y],t);
		for(int i=0;i<4;i++)
		{
			int m=x+dx[i];
			int n=y+dy[i];
			if(m>=0&&n>=0)
				map[m][n]=min(map[m][n],t);
		}
	}
	if(map[0][0]==0)
	{
		cout<<-1;
		return 0;
	}
	q.push({0,0,0});
	vis[0][0]=true;
	while(!q.empty())
	{
		int x=q.front().x,y=q.front().y,t=q.front().t;
		q.pop();
		if(map[x][y]==INF)
		{
			cout<<t;
			return 0;
		}
		for(int i=0;i<4;i++)
		{
			int m=x+dx[i];
			int n=y+dy[i];
			if(m>=0&&m<=350&&n>=0&&n<=350&&map[m][n]>t+1&&!vis[m][n])
				q.push({m,n,t+1}),vis[m][n]=true;
		}
	}
	cout<<-1;
	return 0;
} 
