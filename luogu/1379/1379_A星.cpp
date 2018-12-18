#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int dx[5]={0,1,0,-1,0},dy[5]={0,0,-1,0,1},to=123804765;
int ans[5][5]={ 0,0,0,0,0,
				0,1,2,3,0,
			   	0,8,0,4,0,
			    0,7,6,5,0,
			    0,0,0,0,0};
set<ll> s;
struct node
{
	int g[5][5];
	int val,dep,h,l;
	bool operator > (const node &d) const
	{
		return val>d.val;
	}
	void cal()
	{
		val=0;
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
			{
				if(g[i][j]!=ans[i][j]&&ans[i][j]!=0) val++;
				if(!g[i][j]) h=i,l=j;
			}
		val+=dep;
	}
}a;

priority_queue<node,vector<node>,greater<node> > q;

int bfs()
{
	while(!q.empty())
	{
		a=q.top(),q.pop();
		int x=a.h,y=a.l;
		
		for(int k=1;k<=4;k++)
		{
			int nx=x+dx[k],ny=y+dy[k];
			swap(a.g[nx][ny],a.g[x][y]);
			
			ll num=0;
			for(int i=1;i<=3;i++)
				for(int j=1;j<=3;j++)
					num=num*10+a.g[i][j];	
			if(num==to) return a.dep+1;
								
			if(!s.count(num))
			{
				s.insert(num);
				a.dep++;
				a.cal();
				q.push(a);
				a.dep--;
			}
			swap(a.g[nx][ny],a.g[x][y]);
		}
	}
}

int main()
{
	ll n;
	cin>>n;
	if(n==to) 
		{printf("0");return 0;}
	s.insert(n);
	for(int i=3;i>=1;i--)
		for(int j=3;j>=1;j--)
		{
			a.g[i][j]=n%10,n/=10;
			if(!a.g[i][j]) a.h=i,a.l=j;
		}
	q.push(a);
	
	printf("%d",bfs());
	return 0;
}
