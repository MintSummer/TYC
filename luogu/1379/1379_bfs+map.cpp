#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll to=123804765,n,g[5][5],s[15];
int dx[5]={0,1,0,-1,0},dy[5]={0,0,-1,0,1};
queue<ll> q;
map<ll,int> tim;

void bfs()
{
	q.push(n);
	tim.insert(make_pair(n,0));
	ll x,y;
	int h,l;
	while(!q.empty())
	{
		x=q.front(),q.pop();
		int now=tim[x];
		
		for(int i=3;i>=1;i--)
			for(int j=3;j>=1;j--)
			{
				g[i][j]=x%10,x/=10;
				if(!g[i][j]) h=i,l=j;
				
			}
		
		for(int k=1;k<=4;k++)
		{
			int nx=h+dx[k],ny=l+dy[k];
			if(nx<1&&nx>3&&ny<1&&ny>3) continue;
			swap(g[nx][ny],g[h][l]);
			
			y=0;
			for(int i=1;i<=3;i++)
				for(int j=1;j<=3;j++)
					y=y*10+g[i][j];
			if(!tim.count(y))
				tim.insert(make_pair(y,now+1)),q.push(y);
			if(y==to) return;
			
			swap(g[nx][ny],g[h][l]);
		}
	}
}

int main()
{
	cin>>n;
	bfs();
	cout<<tim[to];
	return 0;
}
