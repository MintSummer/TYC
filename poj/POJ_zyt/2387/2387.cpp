#include<iostream>
#include<cstring>
#include<queue>
#include<climits> 
using namespace std;
struct p
{
	int to;
	int v;
	int next;
}e[4010];
int head[4010],cnt;
int n,t;
queue<int>q;
int vis[1005];
int dis[1005];
void add(int a,int b,int c)
{
	e[cnt].to=b;
	e[cnt].next=head[a];
	e[cnt].v=c;
	head[a]=cnt;
	cnt++;
}
int main(void)
{
	memset(head,-1,sizeof(head));
	cin>>t>>n;
	for(int i=0;i<t;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	for(int i=2;i<=n;i++)
		dis[i]=INT_MAX/2-1;
	vis[1]=true;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=head[u];i!=-1;i=e[i].next)
		{
			int t=e[i].to,v=e[i].v;
			if(dis[t]>dis[u]+v)
			{
				dis[t]=dis[u]+v;
				if(vis[t]==false)
					vis[t]=true,q.push(t);
			}
		}
	}
	cout<<dis[n];
	return 0;
}

