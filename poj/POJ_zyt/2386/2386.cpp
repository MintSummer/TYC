#include<iostream>
#include<queue>
using namespace std;
int n,m,cnt;
struct point
{
	int x;
	int y;
};
queue <point>q;
bool f[110][110];
int main(void)
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char a;
			cin>>a;
			if(a=='W')
				f[i][j]=true;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			{
				if(!f[i][j])continue;
				q.push((point){i,j});
				while(!q.empty())
				{
					point p=q.front();
					q.pop();
					int x=p.x,y=p.y;
					for(int i=x-1;i<=x+1;i++)
						for(int j=y-1;j<=y+1;j++)
							if((i==x&&j==y)||!f[i][j])continue;
							else q.push((point){i,j}),f[i][j]=false;
				}
				cnt++;
			}
	cout<<cnt;
	return 0;
}
